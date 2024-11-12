// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSplinesMultiple.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetRegistryModule.h"

// Sets default values
ATreeSplinesMultiple::ATreeSplinesMultiple()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Set default mesh path
    DefaultTreeMeshPath = TEXT("/Game/CustomModels/tree_ponderosa");
    PineTreeStandardMeshPath = TEXT("/Game/STF/Pack03-LandscapePro/Environment/Foliage/Pines/pine03/SM_pine03.SM_pine03");

    //// Try to load the mesh
    //if (LoadTreeMesh())
    //{
    //    UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh loaded successfully in constructor"));
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("ATreeSplines: Failed to load TreeMesh in constructor"));
    //}
}

// Called when the game starts or when spawned
void ATreeSplinesMultiple::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Hello"));
    if (!TreeInstancedMesh->GetStaticMesh())
    {
        UE_LOG(LogTemp, Warning, TEXT("ATreeSplines: TreeMesh not set in BeginPlay, attempting to load"));
        /*if (LoadTreeMesh())
        {
            UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh loaded successfully in BeginPlay"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ATreeSplines: Failed to load TreeMesh in BeginPlay"));
        }*/
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh already set in BeginPlay"));
    }

}

// Called every frame
void ATreeSplinesMultiple::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ATreeSplinesMultiple::InitializeAvailableCRs()
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FAssetData> AssetData;

    FARFilter Filter;
    Filter.PackagePaths.Add("/Game/CustomModels/trees");
    Filter.ClassNames.Add(UStaticMesh::StaticClass()->GetFName());

    AssetRegistryModule.Get().GetAssets(Filter, AssetData);

    for (const FAssetData& Asset : AssetData)
    {
        FString AssetName = Asset.AssetName.ToString();
        if (AssetName.StartsWith("tree_"))
        {
            TArray<FString> Parts;
            AssetName.ParseIntoArray(Parts, TEXT("_"));
            if (Parts.Num() >= 4)
            {
                int32 SPCD = FCString::Atoi(*Parts[1]);
                float CR = FCString::Atof(*(Parts[2] + "." + Parts[3]));

                if (!AvailableCRs.Contains(SPCD))
                {
                    AvailableCRs.Add(SPCD, TArray<float>());
                }
                AvailableCRs[SPCD].AddUnique(CR);
            }
        }
    }

    // Sort CR values for each SPCD
    for (auto& Pair : AvailableCRs)
    {
        Pair.Value.Sort();
    }
}

float ATreeSplinesMultiple::FindClosestCR(int32 SPCD, float TargetCR)
{
    if (!AvailableCRs.Contains(SPCD))
    {
        UE_LOG(LogTemp, Warning, TEXT("No CR values available for SPCD %d"), SPCD);
        return 0.5f; // Default CR if no match found
    }

    const TArray<float>& CRs = AvailableCRs[SPCD];
    return *Algo::MinElement(CRs, [TargetCR](float A, float B)
        {
            return FMath::Abs(A - TargetCR) < FMath::Abs(B - TargetCR);
        });
}


bool ATreeSplinesMultiple::LoadTreeMesh(int32 SPCD, float CR)
{
    if (IsInGameThread())
    {
        float ClosestCR = FindClosestCR(SPCD, CR);
        FString MeshPath = FString::Printf(TEXT("/Game/CustomModels/trees/tree_%d_%d_%d"),
            SPCD,
            FMath::FloorToInt(ClosestCR),
            FMath::RoundToInt((ClosestCR - FMath::FloorToInt(ClosestCR)) * 100));


        UE_LOG(LogTemp, Log, TEXT("ATreeSplines: Attempting to load TreeMesh: %s"), *MeshPath);

        UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);

        if (!Mesh)
        {
            UE_LOG(LogTemp, Warning, TEXT("ATreeSplines: Failed to load TreeMesh: %s. Using default mesh."), *MeshPath);
            Mesh = LoadObject<UStaticMesh>(nullptr, *DefaultTreeMeshPath);
        }

        if (Mesh)
        {
            TreeInstancedMesh->SetStaticMesh(Mesh);
            UE_LOG(LogTemp, Log, TEXT("ATreeSplines: Successfully loaded TreeMesh: %s"), *MeshPath);
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ATreeSplines: Failed to load TreeMesh: %s and default mesh"), *MeshPath);
            return false;
        }
    }
    else
    {
        AsyncTask(ENamedThreads::GameThread, [this, SPCD, CR]()
            {
                this->LoadTreeMesh(SPCD, CR);
            });
    }
    return false;
}

UOSMUserData* ATreeSplinesMultiple::GetOSMUserData(USplineComponent* SplineComponent)
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


void ATreeSplinesMultiple::ProcessOSMUserData()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("ATreeSplinesMultiple::ProcessOSMUserData: World is null"));
        return;
    }

    InitializeAvailableCRs();

    // Clear existing instances
    for (auto* ISM : TreeInstancedMeshes)
    {
        ISM->ClearInstances();
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
                float Height = 100.0f;
                float Diameter = 50.0f;
                int32 SPCD = 122; // Default SPCD
                float CR = 0.5f; // Default CR

                // Parse OSM data
                for (const auto& Pair : OSMData->Fields)
                {
                    if (Pair.Key == "HT") Height = FCString::Atof(*Pair.Value) * 100.0f;
                    else if (Pair.Key == "DIA") Diameter = FCString::Atof(*Pair.Value) * 50.0f;
                    else if (Pair.Key == "SPCD") SPCD = FCString::Atoi(*Pair.Value);
                    else if (Pair.Key == "CR") CR = FCString::Atof(*Pair.Value);
                }

                UE_LOG(LogTemp, Warning, TEXT("HT: %f, DIA: %f, SPCD: %d, CR: %f"), Height, Diameter, SPCD, CR);

                UInstancedStaticMeshComponent* TreeISM = GetOrCreateTreeInstancedMesh(SPCD, CR);

                if (TreeISM && TreeISM->GetStaticMesh())
                {
                    FTransform TreeTransform = GetTreeTransformAtSplineCenter(SplineComponent, Height, Diameter, TreeISM->GetStaticMesh());
                    TreeISM->AddInstance(TreeTransform);
                    UE_LOG(LogTemp, Warning, TEXT("Added instance for SPCD: %d, CR: %f"), SPCD, CR);
                }
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("ATreeSplinesMultiple::ProcessOSMUserData: Processed tree instances"));
}

UInstancedStaticMeshComponent* ATreeSplinesMultiple::GetOrCreateTreeInstancedMesh(int32 SPCD, float CR)
{
    float ClosestCR = FindClosestCR(SPCD, CR);
    FString MeshPath = FString::Printf(TEXT("/Game/CustomModels/trees/tree_%d_%d_%d"),
        SPCD,
        FMath::FloorToInt(ClosestCR),
        FMath::RoundToInt((ClosestCR - FMath::FloorToInt(ClosestCR)) * 100));

    // Check if we already have an ISM for this mesh
    for (auto* ISM : TreeInstancedMeshes)
    {
        if (ISM->GetStaticMesh() && ISM->GetStaticMesh()->GetPathName() == MeshPath)
        {
            return ISM;
        }
    }

    // If not, create a new one
    UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);
    if (!Mesh)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh: %s. Using default mesh."), *MeshPath);
        Mesh = LoadObject<UStaticMesh>(nullptr, *DefaultTreeMeshPath);
        if (!Mesh)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load default mesh: %s"), *DefaultTreeMeshPath);
            return nullptr;
        }
    }

    UInstancedStaticMeshComponent* NewISM = NewObject<UInstancedStaticMeshComponent>(this, NAME_None, RF_Transactional);
    NewISM->SetStaticMesh(Mesh);
    NewISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    NewISM->SetMobility(EComponentMobility::Static);
    NewISM->SetCastShadow(true);
    NewISM->bCastDynamicShadow = true;
    NewISM->SetEnableGravity(false);
    NewISM->bDisallowNanite = false;
    NewISM->bReceivesDecals = false;
    NewISM->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    NewISM->RegisterComponent();

    TreeInstancedMeshes.Add(NewISM);
    return NewISM;
}

// ... (implement other methods as before, such as InitializeAvailableCRs, FindClosestCR, etc.)

FTransform ATreeSplinesMultiple::GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter, UStaticMesh* TreeMesh)
{
    if (!TreeMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("ATreeSplinesMultiple::GetTreeTransformAtSplineCenter: TreeMesh is not set"));
        return FTransform::Identity;
    }

    float SplineLength = SplineComponent->GetSplineLength();
    FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);
    FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);

    FVector OriginalSize = TreeMesh->GetBoundingBox().GetSize();
    UE_LOG(LogTemp, Warning, TEXT("OriginalSize: %s"), *OriginalSize.ToString());
    float ScaleX = Diameter / OriginalSize.X;
    float ScaleZ = Height / OriginalSize.Z;
    float ScaleY = ScaleX;

    return FTransform(Rotation, Location, FVector(ScaleX, ScaleY, ScaleZ));
}

void ATreeSplinesMultiple::ProcessOSMUserDataFromEditor()
{
#if WITH_EDITOR
    ProcessOSMUserData();
    UE_LOG(LogTemp, Log, TEXT("ProcessOSMUserData called from Editor"));
#endif
}

void ATreeSplinesMultiple::SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter)
{
    if (!TreeInstancedMesh->GetStaticMesh())
    {
        UE_LOG(LogTemp, Error, TEXT("ATreeSplines::SpawnTreeAtSplineCenter: TreeMesh is not set"));
        return;
    }

    // Get the center point of the spline
    float SplineLength = SplineComponent->GetSplineLength();
    FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);
    FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);

    // Get the original mesh bounds to calculate the scale factor
    FVector OriginalSize = TreeInstancedMesh->GetStaticMesh()->GetBoundingBox().GetSize();
    float ScaleX = Diameter / OriginalSize.X;
    float ScaleZ = Height / OriginalSize.Z;
    float ScaleY = ScaleX; // Assuming we want to maintain the aspect ratio for width and depth

    FTransform InstanceTransform(Rotation, Location, FVector(ScaleX, ScaleY, ScaleZ));

    // Set the bDisallowNanite flag to force the use of the fallback mesh
    TreeInstancedMesh->bDisallowNanite = false;

    // Disable decals on the mesh
    TreeInstancedMesh->bReceivesDecals = false;

    // Add instance to the Instanced Static Mesh Component
    TreeInstancedMesh->AddInstance(InstanceTransform);
}