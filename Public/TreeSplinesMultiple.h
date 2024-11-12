//// TreeSplinesMultiple.h
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "Components/SplineComponent.h"
//#include "Components/InstancedStaticMeshComponent.h"
//#include "OSMUserData/OSMUserData.h"
//#include "TreeSplinesMultiple.generated.h"
//
//UCLASS()
//class SPLINEIMPORTER_API ATreeSplinesMultiple : public AActor
//{
//    GENERATED_BODY()
//
//public:
//    // Sets default values for this actor's properties
//    ATreeSplinesMultiple();
//
//protected:
//    // Called when the game starts or when spawned
//    virtual void BeginPlay() override;
//
//public:
//    // Called every frame
//    virtual void Tick(float DeltaTime) override;
//
//    UFUNCTION(BlueprintCallable, Category = "TreeSplines")
//    void ProcessOSMUserData();
//
//    UFUNCTION(CallInEditor, Category = "TreeSplines")
//    void ProcessOSMUserDataFromEditor();
//
//    UPROPERTY(BlueprintReadOnly, Category = "TreeSplines")
//    UInstancedStaticMeshComponent* TreeInstancedMesh;
//
//    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
//    FString DefaultTreeMeshPath;
//
//    /*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TreeSplines")
//    UInstancedStaticMeshComponent* TreeInstancedMesh;
//
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TreeSplines")
//    FString TreeMeshPath;*/
//
//private:
//    void SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);
//    UOSMUserData* GetOSMUserData(USplineComponent* SplineComponent);
//    bool LoadTreeMesh(const FString& TreeID);
//    FTransform GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);
//private:
//    TArray<FTransform> TreeInstances;
//};

// TreeSplinesMultiple.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "OSMUserData/OSMUserData.h"
#include "TreeSplinesMultiple.generated.h"

UCLASS()
class SPLINEIMPORTER_API ATreeSplinesMultiple : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATreeSplinesMultiple();

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

    UPROPERTY(BlueprintReadWrite, Category = "TreeSplines")
    FString PineTreeStandardMeshPath;

private:
    void SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);
    UOSMUserData* GetOSMUserData(USplineComponent* SplineComponent);
    UInstancedStaticMeshComponent* GetOrCreateTreeInstancedMesh(int32 SPCD, float CR);
    bool LoadTreeMesh(int32 SPCD, float CR);
    FTransform GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter, UStaticMesh* TreeMesh);

    void InitializeAvailableCRs();
    float FindClosestCR(int32 SPCD, float TargetCR);

    TArray<FTransform> TreeInstances;
    TMap<int32, TArray<float>> AvailableCRs;

    UPROPERTY()
    TArray<UInstancedStaticMeshComponent*> TreeInstancedMeshes;
};