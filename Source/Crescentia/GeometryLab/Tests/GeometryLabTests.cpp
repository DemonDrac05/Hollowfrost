#include "Misc/AutomationTest.h"
#include "GeometryLab/TreeDeformation.h"

#if WITH_DEV_AUTOMATION_TESTS

constexpr int32 NumSegments = 96, NumRings = 100;
constexpr double Radius = 30.0, Height = 300.0;
constexpr int32 VertexI = 3;
constexpr int32 VertexJ = 51;

namespace GeometryLabTest
{
	constexpr double Tolerance = 0.001;
	
	static double PushOf(const FVector& Before, const FVector& After)
	{
		return Before.Size2D() - After.Size2D();
	}
}
	
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTreeApplyGoldenTest,
	"Crescentia.GeometryLab.Apply.Golden",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FTreeApplyGoldenTest::RunTest(const FString& Parameters)
{
	TArray<FVector>		   Base;
	TArray<FTreeCutRecord> Cuts;
	TArray<FVector>		   Out;
	
	const double Angle = FMath::DegreesToRadians(360.0 * VertexI / NumSegments);
	const double Z = Height * VertexJ / (NumRings - 1);
	Base.Add(FVector(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, Z));
	
	FTreeCutRecord Cut; Cut.Flatness = 3.0; Cut.RimPower = 1.0; Cuts.Add(Cut);
	
	TreeDeformation::Apply(Base, Cuts, Out);
	TestEqual(TEXT("Flatness 3, RimPower 1"), 
			  GeometryLabTest::PushOf(Base[0], Out[0]), 
			  3.4407, 
			  GeometryLabTest::Tolerance);
		
	// Same vertex, Flatness 2, RimPower 2	=> expected: 2.1352
	Cuts[0].Flatness = 2; Cuts[0].RimPower = 2;
	
	TreeDeformation::Apply(Base, Cuts, Out);
	TestEqual(TEXT("Flatness 2, RimPower 2"), 
			  GeometryLabTest::PushOf(Base[0], Out[0]), 
			  2.1352, 
			  GeometryLabTest::Tolerance);
	
	// Same vertex, (2,2), Irregularity 0	=> expected: 1.9336
	Cuts[0].Irregularity = 0;
	
	TreeDeformation::Apply(Base, Cuts, Out);
	TestEqual(TEXT("Flatness 2, RimPower 2, Irregularity 0"), 
			  GeometryLabTest::PushOf(Base[0], Out[0]), 
			  1.9336, 
			  GeometryLabTest::Tolerance);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTreeApplyPropertiesTest,
	"Crescentia.GeometryLab.Apply.Properties",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FTreeApplyPropertiesTest::RunTest(const FString& Parameters)
{
	//
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTreeApplyEdgeCasesTest,
	"Crescentia.GeometryLab.Apply.Properties",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FTreeApplyEdgeCasesTest::RunTest(const FString& Parameters)
{
	//
	return true;
}

#endif
