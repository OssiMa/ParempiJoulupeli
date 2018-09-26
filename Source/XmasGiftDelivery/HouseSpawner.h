#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HouseParent.h"
#include "HouseSpawner.generated.h"

UCLASS()
class XMASGIFTDELIVERY_API AHouseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHouseSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float currentTime;
	int houseNumber;

	FString numberString;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float timerTime;

	FVector spawnLocation;

	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, Category = "Spawnable objects")
		TArray<TSubclassOf<AHouseParent>> spawnableObjects;
};
