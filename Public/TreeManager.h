// TreeManager.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TsISM.h"
#include "TreeManager.generated.h"

UCLASS()
class SPLINEIMPORTER_API ATreeManager : public AActor
{
    GENERATED_BODY()

public:
    ATreeManager();

    UFUNCTION(CallInEditor, Category = "TreeManager")
    void ProcessAllTrees();

private:
    UPROPERTY()
    TMap<FString, ATsISM*> TreeInstances;

    void CreateTreeInstance(int32 SPCD, int32 CRValue);
};