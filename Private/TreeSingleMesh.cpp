// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSingleMesh.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetRegistryModule.h"

// Sets default values
ATreeSingleMesh::ATreeSingleMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Instanced Static Mesh Component
	TreeInstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh"));
	TreeInstancedMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh->SetCastShadow(true);
	TreeInstancedMesh->bCastDynamicShadow = true;
	TreeInstancedMesh->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh->bReceivesDecals = false;

	// add all the tree instanced meshes to the array
	TreeInstancedMeshes.Add(TreeInstancedMesh);

	// set root component to the first instanced mesh
	RootComponent = TreeInstancedMesh;

	// Set default mesh path
	DefaultTreeMeshPath = TEXT("/Game/CustomModels/newTrees/pine_20.pine_20");

}

// Called when the game starts or when spawned
void ATreeSingleMesh::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
	if (!TreeInstancedMesh->GetStaticMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("ATreeSplines: TreeMesh not set in BeginPlay, attempting to load"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ATreeSplines: TreeMesh already set in BeginPlay"));
	}

}

// Called every frame
void ATreeSingleMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ATreeSingleMesh::LoadTreeMesh(int32 SPCD, float CR)
{
	if (!IsInGameThread())
	{
		AsyncTask(ENamedThreads::GameThread, [this, SPCD, CR]()
			{
				this->LoadTreeMesh(SPCD, CR);
			});
		return false;
	}

	if (IsInGameThread())
	{
		FString MeshPath = *DefaultTreeMeshPath;

		// if no mesh path is found, return false
		if (MeshPath.IsEmpty())
		{
			return false;
		}


		//UE_LOG(LogTemp, Log, TEXT("ATreeSplines: Attempting to load TreeMesh: %s"), *MeshPath);

		UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);

		if (!Mesh)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ATreeSplines: Failed to load TreeMesh: %s. Using default mesh."), *MeshPath);
			Mesh = LoadObject<UStaticMesh>(nullptr, *DefaultTreeMeshPath);
		}

		if (Mesh)
		{
			
			TreeInstancedMesh->SetStaticMesh(Mesh);
			//TreeInstancedMesh->SetStaticMesh(Mesh);
			//UE_LOG(LogTemp, Log, TEXT("ATreeSplines: Successfully loaded TreeMesh: %s"), *MeshPath);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ATreeSplines: Failed to load TreeMesh: %s and default mesh"), *MeshPath);
			return false;
		}
	}
	return false;
}

UOSMUserData* ATreeSingleMesh::GetOSMUserData(USplineComponent* SplineComponent)
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


void ATreeSingleMesh::ProcessOSMUserData()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("ATreeSingleMesh::ProcessOSMUserData: World is null"));
		return;
	}

	TreeInstances.Empty();

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

				for (const auto& Pair : OSMData->Fields)
				{
					if (Pair.Key == "HT")
					{
						Height = FCString::Atof(*Pair.Value) * 100.0f;
					}
					else if (Pair.Key == "DIA")
					{
						Diameter = FCString::Atof(*Pair.Value) * 50.0f;
					}
					else if (Pair.Key == "SPCD")
					{
						SPCD = FCString::Atoi(*Pair.Value);
					}
					else if (Pair.Key == "CR")
					{
						CR = FCString::Atof(*Pair.Value);

					}

				}

				// Load the appropriate mesh for this tree
				LoadTreeMesh(SPCD, CR);

				FTransform TreeTransform = GetTreeTransformAtSplineCenter(SplineComponent, Height, Diameter);
				// log the transform
				//UE_LOG(LogTemp, Warning, TEXT("TreeTransform: %s"), *TreeTransform.ToString());

				TreeInstances.Add(TreeTransform);
			}
		}
	}

	TreeInstancedMesh->ClearInstances();
	TreeInstancedMesh->AddInstances(TreeInstances, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh);

	UE_LOG(LogTemp, Log, TEXT("ATreeSingleMesh::ProcessOSMUserData: Added %d tree instances"), TreeInstances.Num());

}

void ATreeSingleMesh::ProcessOSMUserDataFromEditor()
{
#if WITH_EDITOR
	ProcessOSMUserData();
	UE_LOG(LogTemp, Log, TEXT("ProcessOSMUserData called from Editor"));
#endif
}

FTransform ATreeSingleMesh::GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter)
{
	if (!TreeInstancedMesh->GetStaticMesh())
	{
		UE_LOG(LogTemp, Error, TEXT("ATreeSingleMesh::GetTreeTransformAtSplineCenter: TreeMesh is not set"));
		return FTransform::Identity;
	}

	float SplineLength = SplineComponent->GetSplineLength();
	FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);
	FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);

	// apply random rotation relative to tree 
	Rotation.Yaw += FMath::RandRange(-180, 180);

	// make sure the tree is pointed up relative to the spline / world
	Rotation.Pitch = 0;
	Rotation.Roll = 0;

	FVector OriginalSize = TreeInstancedMesh->GetStaticMesh()->GetBoundingBox().GetSize();
	// log original size
	//UE_LOG(LogTemp, Warning, TEXT("OriginalSize: %s"), *OriginalSize.ToString());
	float ScaleX = Diameter / OriginalSize.X;
	float ScaleZ = Height / OriginalSize.Z;
	float ScaleY = ScaleX;

	return FTransform(Rotation, Location, FVector(ScaleX, ScaleY, ScaleZ));
}