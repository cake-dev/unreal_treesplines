// TreeSplinesISM.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "OSMUserData/OSMUserData.h"
#include "TreeSplinesISM.generated.h"

UCLASS()
class SPLINEIMPORTER_API ATreeSplinesISM : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATreeSplinesISM();

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

    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh122_20;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh122_30;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh122_40;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh122_50;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh122_60;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh122_70;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh122_80;

	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh202_10;
	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh202_20;
	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh202_30;
	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh202_40;
	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh202_50;
	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh202_60;
	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh202_70;

	UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
	UInstancedStaticMeshComponent* TreeInstancedMesh66_10;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh66_20;
    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
    UInstancedStaticMeshComponent* TreeInstancedMesh66_30;


    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString DefaultTreeMeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Pine122_020_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Pine122_030_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Pine122_040_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Pine122_050_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Pine122_060_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Pine122_070_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Pine122_080_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
	FString Fir202_010_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Fir202_020_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Fir202_030_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Fir202_040_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Fir202_050_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Fir202_060_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Fir202_070_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
	FString Juniper66_010_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Juniper66_020_MeshPath;

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString Juniper66_030_MeshPath;

private:
    //void SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);
    UOSMUserData* GetOSMUserData(USplineComponent* SplineComponent);
    bool LoadTreeMesh(int32 SPCD, float CR);
    FTransform GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);

    FString GetAppropriateTreeMeshPath(int32 SPCD, float CR);

    TArray<FTransform> TreeInstances;
    TArray<FTransform> TreeInstances122_20transforms;
    TArray<FTransform> TreeInstances122_30transforms;
    TArray<FTransform> TreeInstances122_40transforms;
    TArray<FTransform> TreeInstances122_50transforms;
    TArray<FTransform> TreeInstances122_60transforms;
    TArray<FTransform> TreeInstances122_70transforms;
    TArray<FTransform> TreeInstances122_80transforms;
	TArray<FTransform> TreeInstances202_10transforms;
    TArray<FTransform> TreeInstances202_20transforms;
    TArray<FTransform> TreeInstances202_30transforms;
    TArray<FTransform> TreeInstances202_40transforms;
    TArray<FTransform> TreeInstances202_50transforms;
    TArray<FTransform> TreeInstances202_60transforms;
    TArray<FTransform> TreeInstances202_70transforms;
	TArray<FTransform> TreeInstances66_10transforms;
    TArray<FTransform> TreeInstances66_20transforms;
    TArray<FTransform> TreeInstances66_30transforms;
	TArray< UInstancedStaticMeshComponent*> TreeInstancedMeshes;
};