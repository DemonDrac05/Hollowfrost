#pragma once

#include "WorldGenSettings.h"

namespace WorldGenMath
{
	int32	  DistanceToBorder(int32 X, int32 Y);
	FVector2f ToSideSpace(int32 X, int32 Y, EMapSide Side);
	void	  RemapToPercentile(TArray<float>& Values);
}
