#pragma once

#include "CoreMinimal.h"
#include "TreeCutRecord.h"

namespace TreeDeformation
{
	void Apply(const TArray<FVector>& BaseVertices,
				const TArray<FTreeCutRecord>& Cuts,
				TArray<FVector>& OutVertices);
	
	void RecalculateNormals(const TArray<FVector>& Vertices,
							const TArray<int32>& Triangles,
							TArray<FVector>& OutNormals);
}
