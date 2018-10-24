#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HouseParent.h"
#include "HouseSpawner.generated.h"

UENUM()
enum EDifficultyStage
{
	EASY,
	MEDIUM,
	HARD
};

USTRUCT()
struct FDifficultyCurve
{
public:

	GENERATED_BODY()
		UPROPERTY(EditAnywhere, Category = "DifficultyCurve")
		float timeDecreaseRatio;
	UPROPERTY(EditAnywhere, Category = "DifficultyCurve")
		float houseMoveSpeed;
	int giftsDelivered;
};

UCLASS()
class XMASGIFTDELIVERY_API AHouseSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHouseSpawner();

	FDifficultyCurve easy;
	FDifficultyCurve medium;
	FDifficultyCurve hard;
	EDifficultyStage difficultyStage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void spawnHouse();

	void harderDifficulty(EDifficultyStage);

	float gameTime;
	float currentTime;
	float gameTimer;
	int houseNumber;

	FString numberString;
	FString numberString2;
	FString numberString3;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float timerTime;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float lowLimit;

	bool allowTimeDoubling = true;
	bool allowSpeedingUp = true;

	FVector spawnLocation;

	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, Category = "Spawnable objects")
		TArray<TSubclassOf<AHouseParent>> spawnableObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Present score")
		int presentsDelivered;
};
