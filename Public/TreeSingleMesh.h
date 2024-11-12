// TreeSingleMesh.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "OSMUserData/OSMUserData.h"
#include "TreeSingleMesh.generated.h"

UCLASS()
class SPLINEIMPORTER_API ATreeSingleMesh : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATreeSingleMesh();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "TreeSplines")
    void ProcessOSMUserData();

    UFUNCTION(CallInEditor, Category = "TreeSplines")
    void ProcessOSMUserDataFromEditor();

    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString DefaultTreeMeshPath;

private:
    //void SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);
    UOSMUserData* GetOSMUserData(USplineComponent* SplineComponent);
    bool LoadTreeMesh(int32 SPCD, float CR);
    FTransform GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);

    TArray<FTransform> TreeInstances;
    TArray< UInstancedStaticMeshComponent*> TreeInstancedMeshes;
};