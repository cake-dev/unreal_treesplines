// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSplines.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATreeSplines::ATreeSplines()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set default mesh path
    TreeMeshPath = TEXT("/Game/CustomModels/tree_1");

    // Try to load the mesh
    if (LoadTreeMesh())
    {
        UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh loaded successfully in constructor"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ATreeSplines: Failed to load TreeMesh in constructor"));
    }

}

// Called when the game starts or when spawned
void ATreeSplines::BeginPlay()
{
	Super::BeginPlay();
	// print the word hello
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
    if (!TreeMesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("ATreeSplines: TreeMesh not set in BeginPlay, attempting to load"));
        if (LoadTreeMesh())
        {
            UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh loaded successfully in BeginPlay"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ATreeSplines: Failed to load TreeMesh in BeginPlay"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh already set in BeginPlay"));
    }
	
}

// Called every frame
void ATreeSplines::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATreeSplines::LoadTreeMesh()
{
    if (IsInGameThread())
    { 

        UE_LOG(LogTemp, Log, TEXT("ATreeSplines: Attempting to load TreeMesh"));

        if (TreeMesh)
        {
            UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh is already set"));
            return true;
        }

        if (TreeMeshPath.IsEmpty())
        {
            UE_LOG(LogTemp, Error, TEXT("ATreeSplines: TreeMeshPath is empty"));
            return false;
        }

        TreeMesh = LoadObject<UStaticMesh>(nullptr, *TreeMeshPath);

        if (TreeMesh)
        {
            UE_LOG(LogTemp, Log, TEXT("ATreeSplines: Successfully loaded TreeMesh from path: %s"), *TreeMeshPath);
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ATreeSplines: Failed to load TreeMesh from path: %s"), *TreeMeshPath);
            return false;
        }
    }
    else
    {
        AsyncTask(ENamedThreads::GameThread, [this]()
            {
                this->LoadTreeMesh();
            });
    }
    return false;

}

UOSMUserData* ATreeSplines::GetOSMUserData(USplineComponent* SplineComponent)
{
    const TArray<UAssetUserData*>* UserDataArray = SplineComponent->GetAssetUserDataArray();
    if (UserDataArray)
    {
        for (int32 i = 0; i < UserDataArray->Num(); ++i)
        {
            UAssetUserData* UserData = (*UserDataArray)[i];
            if (UOSMUserData* OSMData = Cast<UOSMUserData>(UserData))
            {
                return OSMData;
            }
        }
    }
    return nullptr;
}

void ATreeSplines::ProcessOSMUserData()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("ATreeSplines::ProcessOSMUserData: World is null"));
        return;
    }

    for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
    {
        TArray<USplineComponent*> SplineComponents;
        ActorItr->GetComponents<USplineComponent>(SplineComponents);

        for (USplineComponent* SplineComponent : SplineComponents)
        {
            UOSMUserData* OSMData = GetOSMUserData(SplineComponent);
            if (OSMData)
            {
                //UE_LOG(LogTemp, Log, TEXT("Processing OSM data for SplineComponent in Actor: %s"), *ActorItr->GetName());

                float Height = 100.0f; // Default height in cm
                float Diameter = 50.0f; // Default diameter in cm

                for (const auto& Pair : OSMData->Fields)
                {
                    //UE_LOG(LogTemp, Log, TEXT("  Key: %s, Value: %s"), *Pair.Key, *Pair.Value);

                    // Here you can process each key-value pair as needed
                    // For example, you might want to store this data, use it to modify the spline, etc.
                    if (Pair.Key == "HT")
                    {
                        // HT unites are in meters
						Height = FCString::Atof(*Pair.Value) * 100.0f; // Convert to cm
                    }
                    else if (Pair.Key == "DIA")
                    {
                        Diameter = FCString::Atof(*Pair.Value) * 50.0f; // Convert to cm
                    }
					else if (Pair.Key == "SPCD")
					{
						// save spcd as a variable
						float spcd = FCString::Atof(*Pair.Value);
					}
                }
                // Spawn a single cone at the center of the spline
                SpawnTreeAtSplineCenter(SplineComponent, Height, Diameter);
            }
        }
    }
}

void ATreeSplines::ProcessOSMUserDataFromEditor()
{
#if WITH_EDITOR
    ProcessOSMUserData();
    UE_LOG(LogTemp, Log, TEXT("ProcessOSMUserData called from Editor"));
#endif
}

void ATreeSplines::SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter)
{
    if (!TreeMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("ATreeSplines::SpawnTreeAtSplineCenter: TreeMesh is not set"));
        return;
    }

    // Get the center point of the spline
    float SplineLength = SplineComponent->GetSplineLength();
    FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);
    FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);

    // Create a unique name for the mesh component
    FString MeshName = FString::Printf(TEXT("TreeMesh_%s"), *SplineComponent->GetName());
    UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(this, *MeshName);
    MeshComponent->SetStaticMesh(TreeMesh);
    MeshComponent->SetWorldLocation(Location);
    MeshComponent->SetWorldRotation(Rotation);

    // Get the original mesh bounds to calculate the scale factor
    FVector OriginalSize = TreeMesh->GetBoundingBox().GetSize();
    float ScaleX = Diameter / OriginalSize.X;
    float ScaleZ = Height / OriginalSize.Z;
    float ScaleY = ScaleX; // Assuming we want to maintain the aspect ratio for width and depth

    MeshComponent->SetRelativeScale3D(FVector(ScaleX, ScaleY, ScaleZ));

    // Set the bDisallowNanite flag to force the use of the fallback mesh
    MeshComponent->bDisallowNanite = true;

	// disable decals on the mesh
	MeshComponent->bReceivesDecals = false;

    MeshComponent->RegisterComponent();
}