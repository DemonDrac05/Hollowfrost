#include "Misc/AutomationTest.h"
#include "WorldGenMath.h"
#include "FarmGrid.h"

// Tests only exist in development builds, never in the shipped game.
#if WITH_DEV_AUTOMATION_TESTS
	
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FToSideSpaceTest,
	"Crescentia.WorldGen.ToSideSpace",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FToSideSpaceTest::RunTest(const FString& Parameters)
{
	// A tile on the east border, row 10.
	const FVector2f East = WorldGenMath::ToSideSpace(UFarmGrid::Width - 1, 10, EMapSide::East);
	TestEqual(TEXT("East: 'along' runs on Y"), East.X, 10.f);
	TestEqual(TEXT("East: border tile is 0 tiles inward"), East.Y, 0.f);
	
	// A tile on the west border, row 10.
	const FVector2f West = WorldGenMath::ToSideSpace(0, 10, EMapSide::West);
	TestEqual(TEXT("West: 'along' runs on Y"), West.X, 10.f);
	TestEqual(TEXT("West: border tile is 0 tiles inward"), West.Y, 0.f);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRemapToPercentileTest,
	"Crescentia.WorldGen.RemapToPercentile",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRemapToPercentileTest::RunTest(const FString& Parameters)
{
	// Expected ranks: -1 -> 0, first 3 -> 0.25, second 3 -> 0.5, 5 -> 0.75, 10 -> 1
	TArray<float> Values = { 5.f, -1.f, 3.f, 3.f, 10.f };
	WorldGenMath::RemapToPercentile(Values);

	TestEqual(TEXT("Lowest value becomes 0"), Values[1], 0.f);
	TestEqual(TEXT("Highest value becomes 1"), Values[4], 1.f);
	TestTrue(TEXT("Ties broken by index: the earlier 3 ranks lower"), Values[2] < Values[3]);

	// Edge case: one value must not divide by zero.
	TArray<float> Single = { 42.f };
	WorldGenMath::RemapToPercentile(Single);
	TestTrue(TEXT("Single value stays finite"), FMath::IsFinite(Single[0]));
	
	return true;
}

#endif