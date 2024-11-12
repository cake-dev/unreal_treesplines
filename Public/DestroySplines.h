// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineImporter/SplineCollection.h"
#include "DestroySplines.generated.h"

UCLASS()
class SPLINEIMPORTER_API ADestroySplines : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADestroySplines();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(CallInEditor)
    void DestroyAllSplineCollections();

private:
    void DestroySplinesAction();
};