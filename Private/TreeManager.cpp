// TreeManager.cpp
#include "TreeManager.h"
#include "EngineUtils.h"

ATreeManager::ATreeManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATreeManager::ProcessAllTrees()
{
    // Clear existing instances
    for (auto& Pair : TreeInstances)
    {
        if (Pair.Value)
        {
            Pair.Value->Destroy();
        }
    }
    TreeInstances.Empty();

    // Create instances for each SPCD and CR combination
    TArray<int32> SPCDs = { 122, 202, 66 };
    TArray<int32> CRValues = { 10, 20, 30, 40, 50, 60, 70, 80 };

    for (int32 SPCD : SPCDs)
    {
        for (int32 CRValue : CRValues)
        {
            CreateTreeInstance(SPCD, CRValue);
        }
    }

    // Process all splines
    UWorld* World = GetWorld();
    if (!World) return;

    for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
    {
        TArray<USplineComponent*> SplineComponents;
        ActorItr->GetComponents<USplineComponent>(SplineComponents);

        for (USplineComponent* SplineComponent : SplineComponents)
        {
            UOSMUserData* OSMData = ATsISM::GetOSMUserData(SplineComponent);
            if (OSMData)
            {
                int32 SPCD = 122; // Default SPCD
                float CR = 0.5f; // Default CR

                for (const auto& Pair : OSMData->Fields)
                {
                    if (Pair.Key == "SPCD")
                    {
                        SPCD = FCString::Atoi(*Pair.Value);
                    }
                    else if (Pair.Key == "CR")
                    {
                        CR = FCString::Atof(*Pair.Value);
                    }
                }

                int32 CRValue = FMath::RoundToInt((1.0f - CR) * 100.0f / 10.0f) * 10;
                CRValue = FMath::Clamp(CRValue, 10, 80);

                FString Key = FString::Printf(TEXT("%d_%d"), SPCD, CRValue);
                ATsISM** FoundInstance = TreeInstances.Find(Key);
                if (FoundInstance && *FoundInstance)
                {
                    (*FoundInstance)->AddTreeInstance(SplineComponent, OSMData);
                }
            }
        }
    }

    // Update all TsISM instances
    for (auto& Pair : TreeInstances)
    {
        if (Pair.Value)
        {
            Pair.Value->UpdateInstances();
        }
    }
}

void ATreeManager::CreateTreeInstance(int32 SPCD, int32 CRValue)
{
    FString Key = FString::Printf(TEXT("%d_%d"), SPCD, CRValue);
    FString MeshPath = ATsISM::GetMeshPathForSPCDAndCR(SPCD, CRValue);

    ATsISM* TreeInstance = GetWorld()->SpawnActor<ATsISM>(ATsISM::StaticClass());
    if (TreeInstance)
    {
        TreeInstance->Initialize(MeshPath);
        TreeInstances.Add(Key, TreeInstance);
    }
}