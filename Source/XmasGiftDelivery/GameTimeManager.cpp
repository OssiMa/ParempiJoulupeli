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

	if (timerOn == false) 
	{
		GetWorldTimerManager().PauseTimer(gameTimeHandle);
	}
	else if (timerOn == true)
	{
		GetWorldTimerManager().UnPauseTimer(gameTimeHandle);
	}
}

UFUNCTION()
void AGameTimeManager::checkTime()
{
	//Check if there's need for harder difficulty
	if (check == 1 && houseSpawner->presentsDelivered >= 2 && houseSpawner->presentsDelivered < 4)
	{
		houseSpawner->harderDifficulty(EASY);
		setTimer(secondTimeCheck);
	}
	else if (check == 2 && houseSpawner->presentsDelivered >= 4 && houseSpawner->presentsDelivered < 6) 
	{
		houseSpawner->harderDifficulty(MEDIUM);
		setTimer(thirdTimeCheck);
	}
	else if (check == 3 && houseSpawner->presentsDelivered >= 6 && houseSpawner->presentsDelivered < 8) 
	{
		houseSpawner->harderDifficulty(HARD);
		GetWorldTimerManager().ClearTimer(gameTimeHandle);
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Nothing.");
	}
}

UFUNCTION()
void AGameTimeManager::setTimer(float timeCheck) 
{
	GetWorldTimerManager().SetTimer(gameTimeHandle, this, &AGameTimeManager::checkTime, timeCheck, false), check++;
}
