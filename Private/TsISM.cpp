// Update TsISM.cpp
#include "TsISM.h"

ATsISM::ATsISM()
{
    PrimaryActorTick.bCanEverTick = false;

    TreeInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh"));
    TreeInstancedMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TreeInstancedMesh->SetMobility(EComponentMobility::Static);
    TreeInstancedMesh->SetCastShadow(true);
    TreeInstancedMesh->bCastDynamicShadow = true;
    TreeInstancedMesh->SetEnableGravity(false);
    TreeInstancedMesh->bDisallowNanite = false;
    TreeInstancedMesh->bReceivesDecals = false;
    RootComponent = TreeInstancedMesh;
}

void ATsISM::Initialize(const FString& MeshPath)
{
    UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);
    if (Mesh)
    {
        TreeInstancedMesh->SetStaticMesh(Mesh);
    }
}

void ATsISM::AddTreeInstance(USplineComponent* SplineComponent, UOSMUserData* OSMData)
{
    float Height = 100.0f;
    float Diameter = 50.0f;

    for (const auto& Pair : OSMData->Fields)
    {
        if (Pair.Key == "HT")
        {
            Height = FCString::Atof(*Pair.Value) * 100.0f;
        }
        else if (Pair.Key == "DIA")
        {
            Diameter = FCString::Atof(*Pair.Value) * 50.0f;
        }
    }

    FTransform TreeTransform = GetTreeTransformAtSplineCenter(SplineComponent, Height, Diameter);
    PendingInstances.Add(TreeTransform);
}

void ATsISM::UpdateInstances()
{
    TreeInstancedMesh->AddInstances(PendingInstances, false);
    PendingInstances.Empty();
}

UOSMUserData* ATsISM::GetOSMUserData(USplineComponent* SplineComponent)
{
    const TArray<UAssetUserData*>* UserDataArray = SplineComponent->GetAssetUserDataArray();
    if (UserDataArray)
    {
        for (UAssetUserData* UserData : *UserDataArray)
        {
            if (UOSMUserData* OSMData = Cast<UOSMUserData>(UserData))
            {
                return OSMData;
            }
        }
    }
    return nullptr;
}

FString ATsISM::GetMeshPathForSPCDAndCR(int32 SPCD, int32 CRValue)
{
    FString BasePath;
    switch (SPCD)
    {
    case 122: BasePath = TEXT("/Game/CustomModels/trees2/pine_"); break;
    case 202: BasePath = TEXT("/Game/CustomModels/trees2/fir_"); break;
    case 66: BasePath = TEXT("/Game/CustomModels/trees2/juniper_"); break;
    default: return TEXT("/Game/CustomModels/trees2/pine_40.pine_40");
    }
    return FString::Printf(TEXT("%s%d.%s%d"), *BasePath, CRValue, *BasePath.Replace(TEXT("/Game/CustomModels/trees2/"), TEXT("")), CRValue);
}

FTransform ATsISM::GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter)
{
    float SplineLength = SplineComponent->GetSplineLength();
    FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);
    FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);

    Rotation.Yaw += FMath::RandRange(-180, 180);
    Rotation.Pitch = 0;
    Rotation.Roll = 0;

    FVector OriginalSize = TreeInstancedMesh->GetStaticMesh()->GetBoundingBox().GetSize();
    float ScaleX = Diameter / OriginalSize.X;
    float ScaleZ = Height / OriginalSize.Z;
    float ScaleY = ScaleX;

    return FTransform(Rotation, Location, FVector(ScaleX, ScaleY, ScaleZ));
}