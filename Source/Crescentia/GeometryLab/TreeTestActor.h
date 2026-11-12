#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"

#include "TreeCutRecord.h"

#include "TreeTestActor.generated.h"

UCLASS()
class CRESCENTIA_API ATreeTestActor : public AActor
{
	GENERATED_BODY()
	
public:
	ATreeTestActor();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, Category = "Trunk")
	float TrunkRadius = 30.0f;
	
	UPROPERTY(EditAnywhere, Category = "Trunk")
	float TrunkHeight = 300.f;
	
	UPROPERTY(EditAnywhere, Category = "Trunk", meta = (ClampMin = "3"))
	int32 NumSegments = 48;
	
	UPROPERTY(EditAnywhere, Category = "Trunk", meta = (ClampMin = "2"))
	int32 NumRings = 32;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProceduralMeshComponent> TrunkMesh;
	
	UPROPERTY(EditAnywhere, Category = "Cuts")
	TArray<FTreeCutRecord> Cuts;
	
	TArray<FVector> BaseVertices;
	TArray<FVector> DeformedVertices;
	
	TArray<int32>		Triangles;
	TArray<FVector>		Normals;
	TArray<FVector2D>	UVs;
	
	void BuildCyclinderData();
	void UploadMesh();
};
