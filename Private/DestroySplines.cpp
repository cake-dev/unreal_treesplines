// Fill out your copyright notice in the Description page of Project Settings.

#include "DestroySplines.h"
#include "EngineUtils.h"
#include "Editor.h"

// Sets default values
ADestroySplines::ADestroySplines()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADestroySplines::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ADestroySplines::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADestroySplines::DestroyAllSplineCollections()
{
#if WITH_EDITOR
    DestroySplinesAction();
    UE_LOG(LogTemp, Log, TEXT("DestroySplines called from Editor"));
#endif
}

void ADestroySplines::DestroySplinesAction()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get World reference"));
        return;
    }

    TArray<AActor*> ActorsToDestroy;
    for (TActorIterator<ASplineCollection> It(World); It; ++It)
    {
        ASplineCollection* SplineCollection = *It;
        if (SplineCollection)
        {
            ActorsToDestroy.Add(SplineCollection);
        }
    }

    for (AActor* Actor : ActorsToDestroy)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Destroyed %d SplineCollection actors"), ActorsToDestroy.Num());
}