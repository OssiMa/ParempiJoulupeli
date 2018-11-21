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
	UFUNCTION(BlueprintCallable, Category = "Make difficulty easier")
		void makeDifficultyEasier();
	void easierDifficulty(float easier);
	UFUNCTION(BlueprintCallable, Category = "Unlock harder difficulty")
		void unlockHarderDifficulty(float harder);
	void checkSpawnTime(float spawnTime);

	UGameInstance* gameInstance;

	float gameTime;
	float currentTime;
	float calculationTimer;
	int houseNumber;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float timeUntilSpawning;
	UPROPERTY(EditAnywhere, Category = "Timer")
		float timeUntilSpawningReduction;
	UPROPERTY(EditAnywhere, Category = "Timer")
		float timeUntilSpawningIncrease;
	UPROPERTY(EditAnywhere, Category = "Timer")
		float lowLimit;
	UPROPERTY(EditAnywhere, Category = "Timer")
		float upperLimit;
	UPROPERTY(EditAnywhere, Category = "Timer")
		float limitBeforeReduction;

	UPROPERTY(EditAnywhere, Category = "House spawning time")
		float easySpawningTime;
	UPROPERTY(EditAnywhere, Category = "House spawning time")
		float mediumSpawningTime;
	UPROPERTY(EditAnywhere, Category = "House spawning time")
		float hardSpawningTime;

	UPROPERTY(EditAnywhere, Category = "House spawning location")
		float spawnLocationX;
	UPROPERTY(EditAnywhere, Category = "House spawning location")
		float spawnLocationZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Present score")
		int presentsDelivered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed modifier")
		float houseMoveSpeedModifierY;
	float houseMoveSpeedModifier;

	FString numberString;
	FString numberString2;
	FString numberString3;
	FString numberString4;
	FString numberString5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Can house spawn?")
		bool canSpawn;
	bool firstSpawned;
	bool allowTimeDoubling;
	bool allowSpeedingUp;

	FVector spawnLocation;

	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, Category = "Spawnable objects")
		TArray<TSubclassOf<AHouseParent>> spawnableObjects;
};
