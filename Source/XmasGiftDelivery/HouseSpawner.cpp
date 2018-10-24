#include "HouseSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Engine.h"


// Sets default values
AHouseSpawner::AHouseSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentTime = 0.0f;

	//spawnRotation.ZeroRotator;
	spawnLocation.X = 200.0f;
	//spawnLocation.Y = 0.0f;
	spawnLocation.Z = -40.0f;

	easy.timeDecreaseRatio = 4.0f;
	easy.houseMoveSpeed = 2.0f;

	medium.timeDecreaseRatio = 3.5f;

	hard.timeDecreaseRatio = 3.0f;
}

// Called when the game starts or when spawned
void AHouseSpawner::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase *gameMode = Cast<AGameModeBase>(GetWorld()->GetAuthGameMode());

	spawnHouse();
}

// Called every frame
void AHouseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime = currentTime + 1 * DeltaTime;

	gameTimer = gameTimer + 1 * DeltaTime;

	if (currentTime >= timerTime)
	{
		spawnHouse();

		currentTime = 0.0f;
	}

	if (gameTimer > 5 && gameTimer < 5.01f && presentsDelivered >= 2 || gameTimer > 20 && gameTimer < 20.01f && presentsDelivered >= 2)
	{
		//gameTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		//FTimespan::FromSeconds(gameTime);


		harderDifficulty(HARD);

		//gameTime = GetWorld()->GetTimeSeconds();

		allowTimeDoubling = false;
	}
	else if (gameTimer )

	if (timerTime <= lowLimit)
	{
		timerTime = lowLimit;
		allowSpeedingUp = false;
	}

	numberString2 = FString::SanitizeFloat(timerTime);
	GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Timer is now: ") + numberString2);

	numberString3 = FString::SanitizeFloat(gameTimer);
	GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Game has been running ") + numberString3, TEXT(" seconds."));
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
}

void AHouseSpawner::harderDifficulty(EDifficultyStage)
{
	switch (difficultyStage)
	{
	case EASY:
		easy.timeDecreaseRatio = 4.0f;
		timerTime = easy.timeDecreaseRatio;
		break;
	case MEDIUM:
		medium.timeDecreaseRatio = 3.5f;
		timerTime = medium.timeDecreaseRatio;
		break;
	case HARD:
		hard.timeDecreaseRatio = 3.0f;
		timerTime = hard.timeDecreaseRatio;
		break;
	default:
		break;
	}
}

