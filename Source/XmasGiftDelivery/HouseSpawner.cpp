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
}

// Called every frame
void AHouseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime = currentTime + 1 * DeltaTime;

	if (currentTime >= timerTime)
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

		currentTime = 0.0f;
	}

	if (allowSpeedingUp) 
	{
		timerTime -= 0.01f * DeltaTime;
	}

	if (timerTime <= lowLimit)
	{
		timerTime = lowLimit;
	}

	numberString2 = FString::SanitizeFloat(timerTime);
	GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Timer is now: ") + numberString2);
}

