#include "TreeDeformation.h"

void TreeDeformation::Apply(const TArray<FVector>& BaseVertices, 
							const TArray<FTreeCutRecord>& Cuts, 
							TArray<FVector>& OutVertices)
{
	OutVertices = BaseVertices;
	
	for (const FTreeCutRecord& Cut : Cuts)
	{
		const FVector Rh = FVector(Cut.LocalPoint.X, Cut.LocalPoint.Y, 0).GetSafeNormal();
		if (Rh.IsNearlyZero() || Cut.Width <= 0.f || Cut.Height <= 0.f) continue;
		
		const FVector S = FVector::CrossProduct(FVector::UpVector, Rh).GetSafeNormal();
		
		for (int32 k = 0; k < BaseVertices.Num(); k++)
		{
			const FVector& V = BaseVertices[k];
			const FVector Flat(V.X, V.Y, 0);
			
			const FVector Rv = Flat.GetSafeNormal();
			
			const double Angle = FMath::Atan2(FVector::DotProduct(S, Rv), FVector::DotProduct(Rh, Rv));
			const double u = Flat.Size() * Angle;
			const double v = V.Z - Cut.LocalPoint.Z;
			
			const double tu = u / Cut.Width;
			const double tv = v / Cut.Height;
			double q = FMath::Sqrt(tu * tu + tv * tv);
			if (q >= 1.0 + Cut.Irregularity) continue;
			
			const double Phi = FMath::Atan2(tv, tu);
			const double Wobble = 0.5 * FMath::Sin(3.0 * Phi + 1.7 * Cut.Seed)
								+ 0.3 * FMath::Sin(5.0 * Phi + 2.9 * Cut.Seed + 1.0)
								+ 0.2 * FMath::Sin(9.0 * Phi + 4.3 * Cut.Seed + 2.0);
			
			q /= 1 + (Cut.Irregularity * Wobble);
			if (q >= 1.0) continue;
			
			const double f = FMath::Pow(1 - FMath::Pow(q, Cut.Flatness), Cut.RimPower);
			
			OutVertices[k] -= Rv * (Cut.Depth * f);
		}
	}
}

void TreeDeformation::RecalculateNormals(const TArray<FVector>& Vertices, 
										 const TArray<int32>& Triangles, 
										 TArray<FVector>& OutNormals)
{
	TArray<FVector> Sums;
	Sums.Init(FVector::ZeroVector, Vertices.Num());
	
	for (int32 t  = 0; t + 2 < Triangles.Num(); t+=3)
	{
		const int32 T0 = Triangles[t];
		const int32 T1 = Triangles[t+1];
		const int32 T2 = Triangles[t+2];
		
		const FVector& V0 = Vertices[T0];
		const FVector& V1 = Vertices[T1];
		const FVector& V2 = Vertices[T2];
		
		const FVector FaceNormal = FVector::CrossProduct(V2 - V0, V1 - V0);
		
		Sums[T0] += FaceNormal;
		Sums[T1] += FaceNormal;
		Sums[T2] += FaceNormal;
	}
	
	auto KeyOf = [](const FVector& P)
	{
		return FIntVector(FMath::RoundToInt(P.X * 1000), 
								FMath::RoundToInt(P.Y * 1000), 
									FMath::RoundToInt(P.Z * 1000));
	};
	
	TMap<FIntVector,FVector> SumAtPosition;
	for (int32 k = 0; k < Vertices.Num(); k++)
	{
		const FIntVector Key = KeyOf(Vertices[k]);
		if (FVector* Found = SumAtPosition.Find(Key))
		{
			*Found += Sums[k];
		}
		else
		{
			SumAtPosition.Add(Key, Sums[k]);
		}
	}
	
	OutNormals.SetNumUninitialized(Vertices.Num());
	for (int32 k = 0; k < Vertices.Num(); k++)
	{
		OutNormals[k] = SumAtPosition[KeyOf(Vertices[k])].GetSafeNormal();
	}
}
