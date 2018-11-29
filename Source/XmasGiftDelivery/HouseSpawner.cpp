#include "HouseSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine.h"
#include "math.h"

// Sets default values
AHouseSpawner::AHouseSpawner()
{
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
	allowTimerCalculation = true;

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

			firstSpawned = true;
		}

		currentTime = currentTime + 1 * DeltaTime;

		if (currentTime >= timeUntilSpawning)
		{
			spawnHouse();

			currentTime = 0.0f;
		}

		if (allowTimerCalculation) 
		{
			calculationTimer = calculationTimer + 1 * DeltaTime;	

			if (calculationTimer >= 5)
			{
				gameTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
				FTimespan::FromSeconds(gameTime);

				if (allowTimeDoubling)
				{
					timeUntilSpawningReduction = timeUntilSpawningReduction - 0.1 * DeltaTime;
				}

				//Calculate reduction time for housespawner
				if (timeUntilSpawningReduction <= limitBeforeReduction && allowSpeedingUp)
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

				allowTimerCalculation = false;
			}

			//Debug messages
			numberString2 = FString::SanitizeFloat(timeUntilSpawning);
			GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Timer is now: ") + numberString2);

			numberString3 = FString::SanitizeFloat(calculationTimer);
			GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Game has been running ") + numberString3, TEXT(" seconds."));
		}	
	}
}

//Calculate the limit when reduction modifier starts to be applied into house spawning time
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

	//Apply house speed modifier
	applySpeedModifier(houseMoveSpeedModifier);
}

//Choose harder difficulty for spawning houses if necessary
void AHouseSpawner::harderDifficulty(EDifficultyStage stage)
{
	switch (stage)
	{
	case EASY:
		timeUntilSpawningReduction = logf(easySpawningTime) / logf(2);
		applySpeedModifier(houseMoveSpeedModifier);
		break;
	case MEDIUM:
		timeUntilSpawningReduction = logf(mediumSpawningTime) / logf(2);
		break;
	case HARD:
		timeUntilSpawningReduction = logf(hardSpawningTime) / logf(2);
		break;
	default:
		break;
	}
}

void AHouseSpawner::makeDifficultyEasier() 
{
	easierDifficulty(timeUntilSpawningIncrease, houseMoveSpeedReduction);
}

//Calculate easier difficulty for spawning houses
void AHouseSpawner::easierDifficulty(float easier, float reduction)
{
	if (timeUntilSpawning < upperLimit)
	{
		allowTimerCalculation = false;
		timeUntilSpawningReduction = timeUntilSpawningReduction + easier;

		//If reduction goes higher than upperlimit, calculate reduction to correspond upperlimit
		if (pow(2, timeUntilSpawningReduction) > upperLimit)
		{
			timeUntilSpawningReduction = logf(upperLimit) / logf(2);
		}

		//Apply new reduction into spawn time once
		timeUntilSpawning = pow(2, timeUntilSpawningReduction);

		if (timeUntilSpawningReduction > limitBeforeReduction) 
		{
			checkSpawnTime(timeUntilSpawning);
		}
	}

	allowTimerCalculation = true;

	//Calculate new move speed for houses
	houseMoveSpeedModifier = houseMoveSpeedModifier - reduction;

	if (houseMoveSpeedModifier <= 0) 
	{
		houseMoveSpeedModifier = 0;
	}
}

void AHouseSpawner::unlockHarderDifficulty(float harder) 
{
	timeUntilSpawning = timeUntilSpawning - harder;
}