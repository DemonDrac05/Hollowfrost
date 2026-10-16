#include "WorldGenMath.h"
#include "FarmGrid.h"

// Distance in tiles from the tile to the nearest map border (0 on the border itself).
int32 WorldGenMath::DistanceToBorder(int32 X, int32 Y)
{
	return FMath::Min(X, Y, UFarmGrid::Width - 1 - X, UFarmGrid::Height - 1 - Y);
}

// Rewrites a tile position relative to one map side:
// X = position along that side, Y = distance inward from it.
// Lets one piece of code handle exits on any side.
FVector2f WorldGenMath::ToSideSpace(int32 X, int32 Y, EMapSide Side)
{
	switch (Side)
	{
		case EMapSide::North: return FVector2f(X, Y);
		case EMapSide::South: return FVector2f(X, UFarmGrid::Height - 1 - Y);
		case EMapSide::West:  return FVector2f(Y, X);
		case EMapSide::East:  return FVector2f(Y, UFarmGrid::Width - 1 - X);
	}
	return FVector2f::ZeroVector;
}

// Replace each value by its rank / (N -1), spreading values evenly over [0,1].
// Afterward, X on every curve means "share of the map": a flat segment 0.6 wide = 60% of tiles.
void WorldGenMath::RemapToPercentile(TArray<float>& Values)
{
	const int32 N = Values.Num();
	
	// One value has no spread to rank against; avoid dividing by zero.
	if (N <= 1) { for (float& V: Values) V = 0.5f; return; }
		
	TArray<int32> Order;
	Order.SetNumUninitialized(N);
	for (int32 i = 0; i < N; i++) Order[i] = i;
		
	// Ties broken by index: equal values always rank the same way, keeping generation deterministic.
	Order.Sort([&Values](const int32 A, const int32 B)
	{
		return Values[A] < Values[B] || (Values[A] == Values[B] && A < B);
	});
		
	for (int32 Rank = 0; Rank < N; Rank++)
	{
		Values[Order[Rank]] = Rank / static_cast<float>(N - 1);
	}
}
