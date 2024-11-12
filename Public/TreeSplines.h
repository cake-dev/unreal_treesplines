// TreeSplines.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "OSMUserData/OSMUserData.h"
#include "TreeSplines.generated.h"

UCLASS()
class SPLINEIMPORTER_API ATreeSplines : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeSplines();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "TreeSplines")
	void ProcessOSMUserData();

	UFUNCTION(CallInEditor, Category = "TreeSplines")
	void ProcessOSMUserDataFromEditor();

	UPROPERTY(EditDefaultsOnly, Category = "TreeSplines")
	UStaticMesh* TreeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TreeSplines")
	FString TreeMeshPath;

private:
	void SpawnTreeAtSplineCenter(USplineComponent* SplineComponent, float Height, float Diameter);
	UOSMUserData* GetOSMUserData(USplineComponent* SplineComponent);
	bool LoadTreeMesh();
};
