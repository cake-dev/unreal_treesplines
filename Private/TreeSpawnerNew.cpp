// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSpawnerNew.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetRegistryModule.h"

// Sets default values
ATreeSpawnerNew::ATreeSpawnerNew()
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

	// Create the Instanced Static Mesh Component for SPCD 122 CR 20
	TreeInstancedMesh122_20 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh122_20"));
	TreeInstancedMesh122_20->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh122_20->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh122_20->SetCastShadow(true);
	TreeInstancedMesh122_20->bCastDynamicShadow = true;
	TreeInstancedMesh122_20->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh122_20->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh122_20->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 122 CR 30
	TreeInstancedMesh122_30 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh122_30"));
	TreeInstancedMesh122_30->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh122_30->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh122_30->SetCastShadow(true);
	TreeInstancedMesh122_30->bCastDynamicShadow = true;
	TreeInstancedMesh122_30->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh122_30->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh122_30->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 122 CR 40
	TreeInstancedMesh122_40 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh122_40"));
	TreeInstancedMesh122_40->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh122_40->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh122_40->SetCastShadow(true);
	TreeInstancedMesh122_40->bCastDynamicShadow = true;
	TreeInstancedMesh122_40->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh122_40->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh122_40->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 122 CR 50
	TreeInstancedMesh122_50 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh122_50"));
	TreeInstancedMesh122_50->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh122_50->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh122_50->SetCastShadow(true);
	TreeInstancedMesh122_50->bCastDynamicShadow = true;
	TreeInstancedMesh122_50->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh122_50->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh122_50->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 122 CR 60
	TreeInstancedMesh122_60 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh122_60"));
	TreeInstancedMesh122_60->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh122_60->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh122_60->SetCastShadow(true);
	TreeInstancedMesh122_60->bCastDynamicShadow = true;
	TreeInstancedMesh122_60->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh122_60->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh122_60->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 122 CR 70
	TreeInstancedMesh122_70 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh122_70"));
	TreeInstancedMesh122_70->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh122_70->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh122_70->SetCastShadow(true);
	TreeInstancedMesh122_70->bCastDynamicShadow = true;
	TreeInstancedMesh122_70->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh122_70->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh122_70->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 122 CR 80
	TreeInstancedMesh122_80 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh122_80"));
	TreeInstancedMesh122_80->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh122_80->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh122_80->SetCastShadow(true);
	TreeInstancedMesh122_80->bCastDynamicShadow = true;
	TreeInstancedMesh122_80->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh122_80->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh122_80->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 202 CR 10
	TreeInstancedMesh202_10 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh202_10"));
	TreeInstancedMesh202_10->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh202_10->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh202_10->SetCastShadow(true);
	TreeInstancedMesh202_10->bCastDynamicShadow = true;
	TreeInstancedMesh202_10->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh202_10->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh202_10->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 202 CR 20
	TreeInstancedMesh202_20 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh202_20"));
	TreeInstancedMesh202_20->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh202_20->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh202_20->SetCastShadow(true);
	TreeInstancedMesh202_20->bCastDynamicShadow = true;
	TreeInstancedMesh202_20->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh202_20->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh202_20->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 202 CR 30
	TreeInstancedMesh202_30 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh202_30"));
	TreeInstancedMesh202_30->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh202_30->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh202_30->SetCastShadow(true);
	TreeInstancedMesh202_30->bCastDynamicShadow = true;
	TreeInstancedMesh202_30->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh202_30->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh202_30->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 202 CR 40
	TreeInstancedMesh202_40 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh202_40"));
	TreeInstancedMesh202_40->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh202_40->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh202_40->SetCastShadow(true);
	TreeInstancedMesh202_40->bCastDynamicShadow = true;
	TreeInstancedMesh202_40->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh202_40->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh202_40->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 202 CR 50
	TreeInstancedMesh202_50 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh202_50"));
	TreeInstancedMesh202_50->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh202_50->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh202_50->SetCastShadow(true);
	TreeInstancedMesh202_50->bCastDynamicShadow = true;
	TreeInstancedMesh202_50->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh202_50->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh202_50->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 202 CR 60
	TreeInstancedMesh202_60 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh202_60"));
	TreeInstancedMesh202_60->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh202_60->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh202_60->SetCastShadow(true);
	TreeInstancedMesh202_60->bCastDynamicShadow = true;
	TreeInstancedMesh202_60->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh202_60->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh202_60->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 202 CR 70
	TreeInstancedMesh202_70 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh202_70"));
	TreeInstancedMesh202_70->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh202_70->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh202_70->SetCastShadow(true);
	TreeInstancedMesh202_70->bCastDynamicShadow = true;
	TreeInstancedMesh202_70->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh202_70->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh202_70->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 66 CR 10
	TreeInstancedMesh66_10 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh66_10"));
	TreeInstancedMesh66_10->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh66_10->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh66_10->SetCastShadow(true);
	TreeInstancedMesh66_10->bCastDynamicShadow = true;
	TreeInstancedMesh66_10->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh66_10->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh66_10->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 66 CR 20
	TreeInstancedMesh66_20 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh66_20"));
	TreeInstancedMesh66_20->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh66_20->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh66_20->SetCastShadow(true);
	TreeInstancedMesh66_20->bCastDynamicShadow = true;
	TreeInstancedMesh66_20->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh66_20->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh66_20->bReceivesDecals = false;

	// Create the Instanced Static Mesh Component for SPCD 66 CR 30
	TreeInstancedMesh66_30 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeInstancedMesh66_30"));
	TreeInstancedMesh66_30->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TreeInstancedMesh66_30->SetMobility(EComponentMobility::Static);
	TreeInstancedMesh66_30->SetCastShadow(true);
	TreeInstancedMesh66_30->bCastDynamicShadow = true;
	TreeInstancedMesh66_30->SetEnableGravity(false);
	// Set the bDisallowNanite flag to force the use of the fallback mesh
	TreeInstancedMesh66_30->bDisallowNanite = false;
	// Disable decals on the mesh
	TreeInstancedMesh66_30->bReceivesDecals = false;

	// add all the tree instanced meshes to the array
	TreeInstancedMeshes.Add(TreeInstancedMesh);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_20);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_30);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_40);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_50);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_60);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_70);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_80);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_10);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_20);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_30);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_40);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_50);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_60);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_70);
	TreeInstancedMeshes.Add(TreeInstancedMesh66_10);
	TreeInstancedMeshes.Add(TreeInstancedMesh66_20);
	TreeInstancedMeshes.Add(TreeInstancedMesh66_30);

	// set root component to the first instanced mesh
	RootComponent = TreeInstancedMesh;

	// Set default mesh path
	DefaultTreeMeshPath = TEXT("/Game/CustomModels/newTrees/pine_20/StaticMeshes/SM_Geometry.SM_Geometry");

	// Set specific tree mesh paths
	Pine122_020_MeshPath = TEXT("/Game/CustomModels/newTrees/pine_20/StaticMeshes/SM_Geometry.SM_Geometry");

	Pine122_030_MeshPath = TEXT("/Game/CustomModels/newTrees/pine_20/StaticMeshes/SM_Geometry.SM_Geometry");

	Pine122_040_MeshPath = TEXT("/Game/CustomModels/newTrees/pine_40/StaticMeshes/SM_Geometry.SM_Geometry");

	Pine122_050_MeshPath = TEXT("/Game/CustomModels/newTrees/pine_50/StaticMeshes/SM_Geometry.SM_Geometry");

	Pine122_060_MeshPath = TEXT("/Game/CustomModels/newTrees/pine_60/StaticMeshes/SM_Geometry.SM_Geometry");

	Pine122_070_MeshPath = TEXT("/Game/CustomModels/newTrees/pine_60/StaticMeshes/SM_Geometry.SM_Geometry");

	Pine122_080_MeshPath = TEXT("/Game/CustomModels/newTrees/pine_80/StaticMeshes/SM_Geometry.SM_Geometry");

	Fir202_010_MeshPath = TEXT("/Game/CustomModels/newTrees/fir_20/StaticMeshes/SM_Geometry.SM_Geometry");

	Fir202_020_MeshPath = TEXT("/Game/CustomModels/newTrees/fir_20/StaticMeshes/SM_Geometry.SM_Geometry");

	Fir202_030_MeshPath = TEXT("/Game/CustomModels/newTrees/fir_20/StaticMeshes/SM_Geometry.SM_Geometry");

	Fir202_040_MeshPath = TEXT("/Game/CustomModels/newTrees/fir_40/StaticMeshes/SM_Geometry.SM_Geometry");

	Fir202_050_MeshPath = TEXT("/Game/CustomModels/newTrees/fir_40/StaticMeshes/SM_Geometry.SM_Geometry");

	Fir202_060_MeshPath = TEXT("/Game/CustomModels/newTrees/fir_40/StaticMeshes/SM_Geometry.SM_Geometry");

	Fir202_070_MeshPath = TEXT("/Game/CustomModels/newTrees/fir_40/StaticMeshes/SM_Geometry.SM_Geometry");

	Juniper66_010_MeshPath = TEXT("/Game/CustomModels/trees2/juniper_10.juniper_10");

	Juniper66_020_MeshPath = TEXT("/Game/CustomModels/trees2/juniper_20.juniper_20");

	Juniper66_030_MeshPath = TEXT("/Game/CustomModels/trees2/juniper_30.juniper_30");

}

// Called when the game starts or when spawned
void ATreeSpawnerNew::BeginPlay()
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
void ATreeSpawnerNew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ATreeSpawnerNew::LoadTreeMesh(int32 SPCD, float CR)
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
		//FString MeshPath = DefaultTreeMeshPath;
		//float cr_complement = 1 - CR; // this is the complement of the crown ratio (i.e. if CR is 0.4, cr_complement is 0.6, will be used to determine the tree mesh to load, 0.6 is closest to 060, so we will load the 060 tree mesh)

		FString MeshPath = GetAppropriateTreeMeshPath(SPCD, CR);

		// if no mesh path is found, return false
		if (MeshPath.IsEmpty())
		{
			//return false;
			MeshPath = DefaultTreeMeshPath;
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
			if (SPCD == 122)
			{
				//TreeInstancedMesh122->SetStaticMesh(Mesh);
				if (MeshPath.Contains("20"))
				{
					TreeInstancedMesh122_20->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("30"))
				{
					TreeInstancedMesh122_30->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("40"))
				{
					TreeInstancedMesh122_40->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("50"))
				{
					TreeInstancedMesh122_50->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("60"))
				{
					TreeInstancedMesh122_60->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("70"))
				{
					TreeInstancedMesh122_70->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("80"))
				{
					TreeInstancedMesh122_80->SetStaticMesh(Mesh);
				}
			}
			else if (SPCD == 202)
			{
				//TreeInstancedMesh202->SetStaticMesh(Mesh);
				if (MeshPath.Contains("10"))
				{
					TreeInstancedMesh202_10->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("20"))
				{
					TreeInstancedMesh202_20->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("30"))
				{
					TreeInstancedMesh202_30->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("40"))
				{
					TreeInstancedMesh202_40->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("50"))
				{
					TreeInstancedMesh202_50->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("60"))
				{
					TreeInstancedMesh202_60->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("70"))
				{
					TreeInstancedMesh202_70->SetStaticMesh(Mesh);
				}
			}
			else if (SPCD == 66)
			{
				//TreeInstancedMesh66->SetStaticMesh(Mesh);
				if (MeshPath.Contains("10"))
				{
					TreeInstancedMesh66_10->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("20"))
				{
					TreeInstancedMesh66_20->SetStaticMesh(Mesh);
				}
				else if (MeshPath.Contains("30"))
				{
					TreeInstancedMesh66_30->SetStaticMesh(Mesh);
				}
			}
			else
			{
				TreeInstancedMesh->SetStaticMesh(Mesh);
			}
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

UOSMUserData* ATreeSpawnerNew::GetOSMUserData(USplineComponent* SplineComponent)
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

FString ATreeSpawnerNew::GetAppropriateTreeMeshPath(int32 SPCD, float CR)
{
	// Calculate the closest CR value
	int32 ClosestCR = FMath::RoundToInt((1.0f - CR) * 100.0f / 10.0f) * 10;
	ClosestCR = FMath::Clamp(ClosestCR, 10, 80);

	// Determine the appropriate mesh path based on SPCD and ClosestCR
	if (SPCD == 122)
	{
		switch (ClosestCR)
		{
		case 20: return Pine122_020_MeshPath;
		case 30: return Pine122_030_MeshPath;
		case 40: return Pine122_040_MeshPath;
		case 50: return Pine122_050_MeshPath;
		case 60: return Pine122_060_MeshPath;
		case 70: return Pine122_070_MeshPath;
		case 80: return Pine122_080_MeshPath;
		default: return Pine122_040_MeshPath; // Default to 40 if no exact match
		}
	}
	else if (SPCD == 202)
	{
		switch (ClosestCR)
		{
		case 10: return Fir202_010_MeshPath;
		case 20: return Fir202_020_MeshPath;
		case 30: return Fir202_030_MeshPath;
		case 40: return Fir202_040_MeshPath;
		case 50: return Fir202_050_MeshPath;
		case 60: return Fir202_060_MeshPath;
		case 70: return Fir202_070_MeshPath;
		default: return Fir202_040_MeshPath; // Default to 40 if no exact match
		}
	}
	else if (SPCD == 66)
	{
		switch (ClosestCR)
		{
		case 10: return Juniper66_010_MeshPath;
		case 20: return Juniper66_020_MeshPath;
		case 30: return Juniper66_030_MeshPath;
		default: return Juniper66_020_MeshPath; // Default to 20 if no exact match
		}
	}

	// If no specific mesh is found, return the default tree mesh path
	return DefaultTreeMeshPath;
}


void ATreeSpawnerNew::ProcessOSMUserData()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("ATreeSpawnerNew::ProcessOSMUserData: World is null"));
		return;
	}

	TreeInstances.Empty();
	TreeInstances122_20transforms.Empty();
	TreeInstances122_30transforms.Empty();
	TreeInstances122_40transforms.Empty();
	TreeInstances122_50transforms.Empty();
	TreeInstances122_60transforms.Empty();
	TreeInstances122_70transforms.Empty();
	TreeInstances122_80transforms.Empty();
	TreeInstances202_10transforms.Empty();
	TreeInstances202_20transforms.Empty();
	TreeInstances202_30transforms.Empty();
	TreeInstances202_40transforms.Empty();
	TreeInstances202_50transforms.Empty();
	TreeInstances202_60transforms.Empty();
	TreeInstances202_70transforms.Empty();
	TreeInstances66_10transforms.Empty();
	TreeInstances66_20transforms.Empty();
	TreeInstances66_30transforms.Empty();

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
						Height = FCString::Atof(*Pair.Value) * 50.0f;
					}
					else if (Pair.Key == "DIA")
					{
						Diameter = FCString::Atof(*Pair.Value) * 25.0f;
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

				// Calculate the closest CR value
				int32 ClosestCR = FMath::RoundToInt((1.0f - CR) * 100.0f / 10.0f) * 10;
				ClosestCR = FMath::Clamp(ClosestCR, 10, 80);

				if (SPCD == 122)
				{
					//TreeInstances122transforms.Add(TreeTransform);
					if (ClosestCR == 20)
					{
						TreeInstances122_20transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 30)
					{
						TreeInstances122_30transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 40)
					{
						TreeInstances122_40transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 50)
					{
						TreeInstances122_50transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 60)
					{
						TreeInstances122_60transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 70)
					{
						TreeInstances122_70transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 80)
					{
						TreeInstances122_80transforms.Add(TreeTransform);
					}
				}
				else if (SPCD == 202)
				{
					//TreeInstances202transforms.Add(TreeTransform);
					if (ClosestCR == 10)
					{
						TreeInstances202_10transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 20)
					{
						TreeInstances202_20transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 30)
					{
						TreeInstances202_30transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 40)
					{
						TreeInstances202_40transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 50)
					{
						TreeInstances202_50transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 60)
					{
						TreeInstances202_60transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 70)
					{
						TreeInstances202_70transforms.Add(TreeTransform);
					}
				}
				else if (SPCD == 66)
				{
					//TreeInstances66transforms.Add(TreeTransform);
					if (ClosestCR == 10)
					{
						TreeInstances66_10transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 20)
					{
						TreeInstances66_20transforms.Add(TreeTransform);
					}
					else if (ClosestCR == 30)
					{
						TreeInstances66_30transforms.Add(TreeTransform);
					}
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("ATreeSpawnerNew::ProcessOSMUserData: Unknown tree loaded"));
					TreeInstances.Add(TreeTransform);
				}

				//TreeInstances.Add(TreeTransform);
			}
		}
	}

	TreeInstancedMesh->ClearInstances();
	TreeInstancedMesh->AddInstances(TreeInstances, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh);

	// add instances for each tree type and crown ratio
	TreeInstancedMesh122_20->ClearInstances();
	TreeInstancedMesh122_20->AddInstances(TreeInstances122_20transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_20);

	TreeInstancedMesh122_30->ClearInstances();
	TreeInstancedMesh122_30->AddInstances(TreeInstances122_30transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_30);

	TreeInstancedMesh122_40->ClearInstances();
	TreeInstancedMesh122_40->AddInstances(TreeInstances122_40transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_40);

	TreeInstancedMesh122_50->ClearInstances();
	TreeInstancedMesh122_50->AddInstances(TreeInstances122_50transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_50);

	TreeInstancedMesh122_60->ClearInstances();
	TreeInstancedMesh122_60->AddInstances(TreeInstances122_60transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_60);

	TreeInstancedMesh122_70->ClearInstances();
	TreeInstancedMesh122_70->AddInstances(TreeInstances122_70transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_70);

	TreeInstancedMesh122_80->ClearInstances();
	TreeInstancedMesh122_80->AddInstances(TreeInstances122_80transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh122_80);

	TreeInstancedMesh202_10->ClearInstances();
	TreeInstancedMesh202_10->AddInstances(TreeInstances202_10transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_10);

	TreeInstancedMesh202_20->ClearInstances();
	TreeInstancedMesh202_20->AddInstances(TreeInstances202_20transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_20);

	TreeInstancedMesh202_30->ClearInstances();
	TreeInstancedMesh202_30->AddInstances(TreeInstances202_30transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_30);

	TreeInstancedMesh202_40->ClearInstances();
	TreeInstancedMesh202_40->AddInstances(TreeInstances202_40transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_40);

	TreeInstancedMesh202_50->ClearInstances();
	TreeInstancedMesh202_50->AddInstances(TreeInstances202_50transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_50);

	TreeInstancedMesh202_60->ClearInstances();
	TreeInstancedMesh202_60->AddInstances(TreeInstances202_60transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_60);

	TreeInstancedMesh202_70->ClearInstances();
	TreeInstancedMesh202_70->AddInstances(TreeInstances202_70transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh202_70);

	TreeInstancedMesh66_10->ClearInstances();
	TreeInstancedMesh66_10->AddInstances(TreeInstances66_10transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh66_10);

	TreeInstancedMesh66_20->ClearInstances();
	TreeInstancedMesh66_20->AddInstances(TreeInstances66_20transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh66_20);

	TreeInstancedMesh66_30->ClearInstances();
	TreeInstancedMesh66_30->AddInstances(TreeInstances66_30transforms, false, true);
	TreeInstancedMeshes.Add(TreeInstancedMesh66_30);

	UE_LOG(LogTemp, Log, TEXT("ATreeSpawnerNew::ProcessOSMUserData: Added %d tree instances"), TreeInstances.Num());

}

void ATreeSpawnerNew::ProcessOSMUserDataFromEditor()
{
#if WITH_EDITOR
	ProcessOSMUserData();
	UE_LOG(LogTemp, Log, TEXT("ProcessOSMUserData called from Editor"));
#endif
}

FTransform ATreeSpawnerNew::GetTreeTransformAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter)
{
	if (!TreeInstancedMesh->GetStaticMesh())
	{
		UE_LOG(LogTemp, Error, TEXT("ATreeSpawnerNew::GetTreeTransformAtSplineCenter: TreeMesh is not set"));
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

//void ATreeSpawnerNew::SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter)
//{
//    if (!TreeInstancedMesh->GetStaticMesh())
//    {
//        UE_LOG(LogTemp, Error, TEXT("ATreeSplines::SpawnTreeAtSplineCenter: TreeMesh is not set"));
//        return;
//    }
//
//    // Get the center point of the spline
//    float SplineLength = SplineComponent->GetSplineLength();
//    FVector Location = SplineComponent->GetLocationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);
//    FRotator Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(SplineLength * 0.5f, ESplineCoordinateSpace::World);
//
//    // Get the original mesh bounds to calculate the scale factor
//    FVector OriginalSize = TreeInstancedMesh->GetStaticMesh()->GetBoundingBox().GetSize();
//    float ScaleX = Diameter / OriginalSize.X;
//    float ScaleZ = Height / OriginalSize.Z;
//    float ScaleY = ScaleX; // Assuming we want to maintain the aspect ratio for width and depth
//
//    FTransform InstanceTransform(Rotation, Location, FVector(ScaleX, ScaleY, ScaleZ));
//
//    // Set the bDisallowNanite flag to force the use of the fallback mesh
//    TreeInstancedMesh->bDisallowNanite = false;
//
//    // Disable decals on the mesh
//    TreeInstancedMesh->bReceivesDecals = false;
//
//    // Add instance to the Instanced Static Mesh Component
//    TreeInstancedMesh->AddInstance(InstanceTransform);
//}