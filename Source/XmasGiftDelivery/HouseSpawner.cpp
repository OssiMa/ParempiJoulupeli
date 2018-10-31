#include "HouseSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine.h"


// Sets default values
AHouseSpawner::AHouseSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentTime = 0.0f;

	spawnLocation.X = 200.0f;
	//spawnLocation.Y = 0.0f;
	spawnLocation.Z = -40.0f;
}

// Called when the game starts or when spawned
void AHouseSpawner::BeginPlay()
{
	Super::BeginPlay();

	//AGameModeBase *gameMode = Cast<AGameModeBase>(GetWorld()->GetAuthGameMode());
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

			//timeUntilSpawning = pow (2, 1/gameTime);

			if (allowTimeDoubling)
			{
				timeUntilSpawningReduction = timeUntilSpawningReduction - 0.1 * DeltaTime;
			}

			if (timeUntilSpawningReduction <= 2.3f)
			{
				allowTimeDoubling = false;
				timeUntilSpawningReduction = timeUntilSpawningReduction - 0.02 * DeltaTime;
				timeUntilSpawning = pow(2, timeUntilSpawningReduction);
			}
		}

		if (timeUntilSpawning <= lowLimit)
		{
			timeUntilSpawning = lowLimit;
			allowSpeedingUp = false;
		}

		numberString2 = FString::SanitizeFloat(timeUntilSpawning);
		GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Timer is now: ") + numberString2);

		numberString3 = FString::SanitizeFloat(calculationTimer);
		GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Game has been running ") + numberString3, TEXT(" seconds."));
	}
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
	AHouseParent* newObject = GetWorld()->SpawnActor<AHouseParent>(spawnableObjects[houseNumber], spawnLocation, spawnRotation, spawnParams);

	if (firstSpawned == false) 
	{
		firstSpawned = true;
	}
}

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

