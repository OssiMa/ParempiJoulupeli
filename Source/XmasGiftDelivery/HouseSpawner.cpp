#include "HouseSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"
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
}

// Called when the game starts or when spawned
void AHouseSpawner::BeginPlay()
{
	Super::BeginPlay();

	spawnHouse();
}

// Called every frame
void AHouseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime = currentTime + 1 * DeltaTime;

	oldCurrentTime = oldCurrentTime + 1 * DeltaTime;

	if (currentTime >= timerTime)
	{
		spawnHouse();

		currentTime = 0.0f;
	}
	/*
	if (oldCurrentTime < 1) 
	{
		allowTimeDoubling = true;
	}*/
	if (gameTime >= 5 && allowTimeDoubling == true) 
	{
		timeDecreaseRatio *= 2;

		gameTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		FTimespan::FromSeconds(gameTime);

		//numberString3 = FString::SanitizeFloat(gameTime);
		//GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Game has been running ") + numberString3, TEXT(" seconds."));

		allowTimeDoubling = false;
		oldCurrentTime = 0;
	}

	if (allowSpeedingUp) 
	{
		timerTime -= timeDecreaseRatio * DeltaTime;
	}

	if (timerTime <= lowLimit)
	{
		timerTime = lowLimit;
		allowSpeedingUp = false;
	}

	numberString2 = FString::SanitizeFloat(timerTime);
	GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Timer is now: ") + numberString2);
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

