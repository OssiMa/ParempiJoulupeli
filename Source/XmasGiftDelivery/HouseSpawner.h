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

	void spawnHouse();

	float gameTime;
	float currentTime;
	float oldCurrentTime;
	int houseNumber;

	FString numberString;
	FString numberString2;
	FString numberString3;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float timerTime;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float timeDecreaseRatio;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float lowLimit;

	bool allowTimeDoubling = true;
	bool allowSpeedingUp = true;

	FVector spawnLocation;

	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, Category = "Spawnable objects")
		TArray<TSubclassOf<AHouseParent>> spawnableObjects;
};
