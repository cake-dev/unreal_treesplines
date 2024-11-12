// FireStarter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "FireStarter.generated.h"

USTRUCT()
struct FGridCell
{
    GENERATED_BODY()

    UPROPERTY()
    bool bIsOnFire;

    UPROPERTY()
    FVector Location;

    FGridCell() : bIsOnFire(false), Location(FVector::ZeroVector) {}
};

UCLASS()
class SPLINEIMPORTER_API AFireStarter : public AActor
{
    GENERATED_BODY()

public:
    AFireStarter();
    virtual void Tick(float DeltaTime) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(BlueprintCallable, Category = "Fire")
    void StartFire();

    UFUNCTION(CallInEditor, Category = "Fire")
    void StartFireInEditor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* FireEffectTemplate;

    UPROPERTY(EditDefaultsOnly, Category = "Fire")
    float CellSize = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Fire")
    float FireSpreadInterval = 2.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Fire")
    float FireLifetime = 5.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Fire")
    int32 GridSize = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Fire")
    float RaycastHeight = 1000.0f;

    FTimerHandle FireSpreadTimerHandle;

    TArray<FGridCell> Grid;
    TArray<UParticleSystemComponent*> ActiveFireEffects;

    void InitializeGrid();
    void SpreadFire();
    void ExtinguishFire(int32 Index);
    int32 GetCellIndex(const FVector& Location);
    TArray<int32> GetAdjacentCells(int32 Index);
    void CleanupFireEffects();
    FVector GetLandscapeLocationForFire(const FVector& TargetLocation);
    UParticleSystemComponent* SpawnFireEffect(const FVector& Location);
    void ManageActiveFireEffects();
    void Destroyed();
    void PreEditChange(FProperty* PropertyAboutToChange);
    void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
};