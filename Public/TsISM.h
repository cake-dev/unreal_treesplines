// Update TsISM.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "OSMUserData/OSMUserData.h"
#include "TsISM.generated.h"

UCLASS()
class SPLINEIMPORTER_API ATsISM : public AActor
{
    GENERATED_BODY()

public:
    ATsISM();

    void Initialize(const FString& MeshPath);
    void AddTreeInstance(USplineComponent* SplineComponent, UOSMUserData* OSMData);
    void UpdateInstances();

    static UOSMUserData* GetOSMUserData(USplineComponent* SplineComponent);
    static FString GetMeshPathForSPCDAndCR(int32 SPCD, int32 CRValue);

private:
    UPROPERTY()
    UInstancedStaticMeshComponent* TreeInstancedMesh;

    TArray<FTransform> PendingInstances;

    FTransform GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);
};
