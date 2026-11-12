#include "TreeTestActor.h"

#include "TreeDeformation.h"

ATreeTestActor::ATreeTestActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	TrunkMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TrunkMesh"));
	SetRootComponent(TrunkMesh);
}

void ATreeTestActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	BuildCyclinderData();
	
	TreeDeformation::Apply(BaseVertices,Cuts,DeformedVertices);
	TreeDeformation::RecalculateNormals(DeformedVertices,Triangles,Normals);
	
	UploadMesh();
}

void ATreeTestActor::BuildCyclinderData()
{
	BaseVertices.Reset();
	DeformedVertices.Reset();
	
	Triangles.Reset();
	Normals.Reset();
	UVs.Reset();
	
	const int32 N = NumSegments;
	const int32 M = NumRings;
	const int32 Stride = N + 1;

	for (int32 j  = 0; j < M; ++j)
	{
		const float z = TrunkHeight * (static_cast<float>(j) / static_cast<float>(M - 1));
		
		for (int32 i = 0; i <= N; ++i)
		{
			const float Angle = (2 * UE_PI * i) / N;
			const float c = cos(Angle);
			const float s = sin(Angle);
			
			BaseVertices.Add(FVector(TrunkRadius * c, TrunkRadius * s, z));
			
			Normals.Add(FVector(c, s, 0.f));
			UVs.Add(FVector2D(static_cast<float>(i) / N, static_cast<float>(j) / (M - 1)));
		}
	}
	
	for (int32 j  = 0; j < M - 1; ++j)
	{
		for (int32 i = 0; i < N; ++i)
		{
			const int32 A = j * Stride + i;
			const int32 B = A + 1;
			const int32 C = A + Stride;
			const int32 D = C + 1;
			
			Triangles.Add(A); Triangles.Add(C); Triangles.Add(B);
			Triangles.Add(B); Triangles.Add(C); Triangles.Add(D);
		}
	}
	
	DeformedVertices = BaseVertices;
}

void ATreeTestActor::UploadMesh()
{
	TrunkMesh->CreateMeshSection(
		0,
		DeformedVertices,
		Triangles,
		Normals,
		UVs,
		TArray<FColor>(),
		TArray<FProcMeshTangent>(),
		false);
}
