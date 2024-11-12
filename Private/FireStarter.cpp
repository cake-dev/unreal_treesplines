// FireStarter.cpp
#include "FireStarter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AFireStarter::AFireStarter()
{
    PrimaryActorTick.bCanEverTick = true;

    FireEffectTemplate = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireEffectTemplate"));
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    static ConstructorHelpers::FObjectFinder<UParticleSystem> FireParticleSystem(TEXT("/Game/M5VFXVOL2/Particles/Fire/Fire_00.Fire_00"));
    if (FireParticleSystem.Succeeded())
    {
        FireEffectTemplate->SetTemplate(FireParticleSystem.Object);
    }

    // Ensure we receive notifications when the actor is being destroyed
    bAllowTickBeforeBeginPlay = false;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFireStarter::BeginPlay()
{
    Super::BeginPlay();
    InitializeGrid();
}

void AFireStarter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ManageActiveFireEffects();
}

void AFireStarter::InitializeGrid()
{
    Grid.Empty();
    float HalfGridSize = (GridSize * CellSize) / 2.0f;
    FVector ActorLocation = GetActorLocation();

    for (int32 x = 0; x < GridSize; ++x)
    {
        for (int32 y = 0; y < GridSize; ++y)
        {
            FGridCell Cell;
            FVector CellCenter = ActorLocation + FVector(
                (x * CellSize) - HalfGridSize,
                (y * CellSize) - HalfGridSize,
                0
            );
            Cell.Location = GetLandscapeLocationForFire(CellCenter);
            Grid.Add(Cell);
        }
    }
}

void AFireStarter::Destroyed()
{
    // This gets called both in-game and in editor when the actor is destroyed
    CleanupFireEffects();
    Super::Destroyed();
}

void AFireStarter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CleanupFireEffects();
    Super::EndPlay(EndPlayReason);
}

void AFireStarter::StartFire()
{
    int32 CenterIndex = (GridSize * GridSize) / 2;
    Grid[CenterIndex].bIsOnFire = true;

    UParticleSystemComponent* FireEffect = SpawnFireEffect(Grid[CenterIndex].Location);
    ActiveFireEffects.Add(FireEffect);

    GetWorldTimerManager().SetTimer(FireSpreadTimerHandle, this, &AFireStarter::SpreadFire, FireSpreadInterval, true);
    FTimerHandle ExtinguishTimerHandle;
    GetWorldTimerManager().SetTimer(ExtinguishTimerHandle, [this, CenterIndex]() { ExtinguishFire(CenterIndex); }, FireLifetime, false);
}

void AFireStarter::SpreadFire()
{
    TArray<int32> BurningCells;
    for (int32 i = 0; i < Grid.Num(); ++i)
    {
        if (Grid[i].bIsOnFire)
        {
            BurningCells.Add(i);
        }
    }

    for (int32 BurningCell : BurningCells)
    {
        TArray<int32> AdjacentCells = GetAdjacentCells(BurningCell);
        int32 RandomAdjacentCell = AdjacentCells[FMath::RandRange(0, AdjacentCells.Num() - 1)];

        if (!Grid[RandomAdjacentCell].bIsOnFire)
        {
            Grid[RandomAdjacentCell].bIsOnFire = true;

            UParticleSystemComponent* FireEffect = SpawnFireEffect(Grid[RandomAdjacentCell].Location);
            ActiveFireEffects.Add(FireEffect);

            FTimerHandle ExtinguishTimerHandle;
            GetWorldTimerManager().SetTimer(ExtinguishTimerHandle, [this, RandomAdjacentCell]() { ExtinguishFire(RandomAdjacentCell); }, FireLifetime, false);
        }
    }
}

void AFireStarter::ExtinguishFire(int32 Index)
{
    if (Index >= 0 && Index < Grid.Num())
    {
        Grid[Index].bIsOnFire = false;
        if (ActiveFireEffects.IsValidIndex(Index) && ActiveFireEffects[Index])
        {
            ActiveFireEffects[Index]->DeactivateSystem();
            ActiveFireEffects[Index]->DestroyComponent();
            ActiveFireEffects[Index] = nullptr;
        }
    }

    // Check if all fires are extinguished
    bool bAnyFireActive = false;
    for (const FGridCell& Cell : Grid)
    {
        if (Cell.bIsOnFire)
        {
            bAnyFireActive = true;
            break;
        }
    }

    if (!bAnyFireActive)
    {
        GetWorldTimerManager().ClearTimer(FireSpreadTimerHandle);
    }
}

FVector AFireStarter::GetLandscapeLocationForFire(const FVector& TargetLocation)
{
    FHitResult HitResult;
    FVector StartLocation = TargetLocation + FVector(0, 0, RaycastHeight);
    FVector EndLocation = TargetLocation - FVector(0, 0, RaycastHeight);

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
    {
        // Draw debug line to visualize the raycast
        DrawDebugLine(GetWorld(), StartLocation, HitResult.Location, FColor::Green, false, 1.0f);

        // Draw debug point at the hit location
        DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Red, false, 1.0f);

        return HitResult.Location;
    }

    // If no hit, return the original target location
    return TargetLocation;
}

int32 AFireStarter::GetCellIndex(const FVector& Location)
{
    FVector LocalLocation = Location - GetActorLocation();
    float HalfGridSize = (GridSize * CellSize) / 2.0f;
    int32 X = FMath::Clamp(FMath::FloorToInt((LocalLocation.X + HalfGridSize) / CellSize), 0, GridSize - 1);
    int32 Y = FMath::Clamp(FMath::FloorToInt((LocalLocation.Y + HalfGridSize) / CellSize), 0, GridSize - 1);
    return Y * GridSize + X;
}

TArray<int32> AFireStarter::GetAdjacentCells(int32 Index)
{
    TArray<int32> AdjacentCells;
    int32 X = Index % GridSize;
    int32 Y = Index / GridSize;

    for (int32 dx = -1; dx <= 1; ++dx)
    {
        for (int32 dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0) continue;

            int32 NewX = X + dx;
            int32 NewY = Y + dy;

            if (NewX >= 0 && NewX < GridSize && NewY >= 0 && NewY < GridSize)
            {
                AdjacentCells.Add(NewY * GridSize + NewX);
            }
        }
    }

    return AdjacentCells;
}

UParticleSystemComponent* AFireStarter::SpawnFireEffect(const FVector& Location)
{
    UParticleSystemComponent* FireEffect = UGameplayStatics::SpawnEmitterAtLocation(
        GetWorld(),
        FireEffectTemplate->Template,
        Location,
        FRotator::ZeroRotator,
        FVector(1.0f),
        true
    );

    return FireEffect;
}

void AFireStarter::ManageActiveFireEffects()
{
    for (int32 i = ActiveFireEffects.Num() - 1; i >= 0; --i)
    {
        if (ActiveFireEffects[i] && !ActiveFireEffects[i]->IsActive())
        {
            ActiveFireEffects[i]->DestroyComponent();
            ActiveFireEffects.RemoveAt(i);
        }
    }
}

void AFireStarter::CleanupFireEffects()
{
    // Stop the spread timer first
    GetWorldTimerManager().ClearTimer(FireSpreadTimerHandle);

    // Clean up all active fire effects
    for (UParticleSystemComponent* FireEffect : ActiveFireEffects)
    {
        if (FireEffect && !FireEffect->IsBeingDestroyed())
        {
            FireEffect->DeactivateSystem();
            FireEffect->DestroyComponent();
        }
    }
    ActiveFireEffects.Empty();

    // Clear the grid
    Grid.Empty();
}

void AFireStarter::StartFireInEditor()
{
#if WITH_EDITOR
    CleanupFireEffects(); // Clean up any existing fire effects
    InitializeGrid();
    StartFire();
    UE_LOG(LogTemp, Log, TEXT("Fire started from editor button at location: %s"), *GetActorLocation().ToString());
#endif
}

#if WITH_EDITOR
void AFireStarter::PreEditChange(FProperty* PropertyAboutToChange)
{
    // Called before property changes in editor
    Super::PreEditChange(PropertyAboutToChange);
}

void AFireStarter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    // Called after property changes in editor
    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif