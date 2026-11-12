#pragma once

#include "CoreMinimal.h"
#include "TreeCutRecord.generated.h"

USTRUCT(BlueprintType)
struct FTreeCutRecord
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut")
	FVector LocalPoint = FVector(30.f, 0.f, 150.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut")
	FVector LocalNormal = FVector(1.f, 0.f, 0.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut")
	float Width = 12.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut")
	float Height = 18.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut")
	float Depth = 4.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut", meta = (ClampMin = "1", ClampMax= "8"))
	float Flatness = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut", meta = (ClampMin = "0.3", ClampMax = "3"))
	float RimPower = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut", meta = (ClampMin = "0", ClampMax = "0.5"))
	float Irregularity = .15f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cut")
	int32 Seed = 0;
};
