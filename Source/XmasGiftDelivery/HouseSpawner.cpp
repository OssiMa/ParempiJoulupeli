#include "HouseSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine.h"
#include "math.h"


// Sets default values
AHouseSpawner::AHouseSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentTime = 0.0f;
}

// Called when the game starts or when spawned
void AHouseSpawner::BeginPlay()
{
	Super::BeginPlay();

	spawnLocation.X = spawnLocationX;
	spawnLocation.Z = spawnLocationZ;

	allowTimeDoubling = true;
	allowSpeedingUp = true;

	checkSpawnTime(timeUntilSpawning);
}

// Called every frame
void AHouseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (canSpawn)
	{
		if (firstSpawned == false)
		{
			spawnHouse();
		}

		currentTime = currentTime + 1 * DeltaTime;

		calculationTimer = calculationTimer + 1 * DeltaTime;

		if (currentTime >= timeUntilSpawning)
		{
			spawnHouse();

			currentTime = 0.0f;
		}

		if (calculationTimer >= 5)
		{
			gameTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
			FTimespan::FromSeconds(gameTime);

			if (allowTimeDoubling)
			{
				timeUntilSpawningReduction = timeUntilSpawningReduction - 0.1 * DeltaTime;
			}

			//Calculate reduction time for housespawner
			if (timeUntilSpawningReduction <= limitBeforeReduction)
			{
				allowTimeDoubling = false;
				timeUntilSpawningReduction = timeUntilSpawningReduction - 0.02 * DeltaTime;
				timeUntilSpawning = pow(2, timeUntilSpawningReduction);

				houseMoveSpeedModifier = houseMoveSpeedModifier + houseMoveSpeedModifierY * DeltaTime;
			}
		}

		if (timeUntilSpawning <= lowLimit)
		{
			timeUntilSpawning = lowLimit;
			allowSpeedingUp = false;
		}

		//Debug messages
		numberString2 = FString::SanitizeFloat(timeUntilSpawning);
		GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Timer is now: ") + numberString2);

		numberString3 = FString::SanitizeFloat(calculationTimer);
		GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Game has been running ") + numberString3, TEXT(" seconds."));
	}
}

void AHouseSpawner::checkSpawnTime(float spawnTime) 
{
	limitBeforeReduction = logf(spawnTime) / logf(2);

	numberString5 = FString::SanitizeFloat(limitBeforeReduction);
	GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("LimitBeforeReduction is now ") + numberString5);
}

void AHouseSpawner::spawnHouse()
{
	//Generate random number for the house spawner
	houseNumber = FMath::RandRange(0, 2);

	//Debug message
	numberString = FString::SanitizeFloat(houseNumber);
	GEngine->AddOnScreenDebugMessage(-2, 2.f, FColor::Red, TEXT("The random number is ") + numberString);

	//Set some spawn parameters
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;

	//Spawn the object
	AHouseParent *newObject = GetWorld()->SpawnActor<AHouseParent>(spawnableObjects[houseNumber], spawnLocation, spawnRotation, spawnParams);

	newObject->applyHouseSpeed(houseMoveSpeedModifier);

	if (firstSpawned == false)
	{
		firstSpawned = true;
	}
}

//Choose harder difficulty if necessary
void AHouseSpawner::harderDifficulty(EDifficultyStage stage)
{
	switch (stage)
	{
	case EASY:
		timeUntilSpawning = easySpawningTime;
		break;
	case MEDIUM:
		timeUntilSpawning = mediumSpawningTime;
		break;
	case HARD:
		timeUntilSpawning = hardSpawningTime;
		break;
	default:
		break;
	}

	numberString4 = FString::SanitizeFloat(timeUntilSpawning);
	GEngine->AddOnScreenDebugMessage(-2, 2.f, FColor::Red, TEXT("Timeuntilspawning is ") + numberString4);
}

void AHouseSpawner::makeDifficultyEasier() 
{
	easierDifficulty(timeUntilSpawningIncrease);
}

void AHouseSpawner::easierDifficulty(float easier)
{
	if (timeUntilSpawning < upperLimit)
	{
		timeUntilSpawning = timeUntilSpawning + easier;

		if (timeUntilSpawning > upperLimit) 
		{
			timeUntilSpawning = upperLimit;
		}

		checkSpawnTime(timeUntilSpawning);
	}
	else
	{
		timeUntilSpawning = upperLimit;

		checkSpawnTime(timeUntilSpawning);
	}
}

void AHouseSpawner::unlockHarderDifficulty(float harder) 
{
	timeUntilSpawning = timeUntilSpawning - harder;
}