#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "math.h"
#include "HouseParent.h"
#include "HouseSpawner.generated.h"

UENUM()
enum EDifficultyStage
{
	EASY,
	MEDIUM,
	HARD
};

UCLASS()
class XMASGIFTDELIVERY_API AHouseSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHouseSpawner();

	EDifficultyStage difficultyStage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void spawnHouse();

	void harderDifficulty(EDifficultyStage stage);

	UGameInstance* gameInstance;

	float gameTime;
	float currentTime;
	float calculationTimer;
	int houseNumber;

	UPROPERTY(EditAnywhere, Category = "House spawning time")
		float easySpawningTime;
	UPROPERTY(EditAnywhere, Category = "House spawning time")
		float mediumSpawningTime;
	UPROPERTY(EditAnywhere, Category = "House spawning time")
		float hardSpawningTime;

	FString numberString;
	FString numberString2;
	FString numberString3;
	FString numberString4;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float timeUntilSpawning;
	UPROPERTY(EditAnywhere, Category = "Timer")
		float timeUntilSpawningReduction;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float lowLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Present score")
	bool canSpawn = true;
	bool allowTimeDoubling = true;
	bool allowSpeedingUp = true;

	FVector spawnLocation;

	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, Category = "Spawnable objects")
		TArray<TSubclassOf<AHouseParent>> spawnableObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Present score")
		int presentsDelivered;
};
