#include "GameTimeManager.h"


// Sets default values
AGameTimeManager::AGameTimeManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameTimeManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(gameTimeHandle, this, &AGameTimeManager::checkTime, firstTimeCheck, false), check++;
}

// Called every frame
void AGameTimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UFUNCTION()
void AGameTimeManager::checkTime()
{
	if (check == 1 && houseSpawner->presentsDelivered >= 2 && houseSpawner->presentsDelivered < 4)
	{
		houseSpawner->harderDifficulty(EASY);
	}
	else if (check == 2 && houseSpawner->presentsDelivered >= 4 && houseSpawner->presentsDelivered < 6) 
	{
		houseSpawner->harderDifficulty(MEDIUM);
	}
	else if (check == 3 && houseSpawner->presentsDelivered >= 6 && houseSpawner->presentsDelivered < 8) 
	{
		houseSpawner->harderDifficulty(HARD);
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Nothing.");
	}

	GetWorldTimerManager().ClearTimer(gameTimeHandle);
}

