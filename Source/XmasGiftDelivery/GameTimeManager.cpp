#include "GameTimeManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TimerManager.h"
#include "Engine.h"
#include "HouseSpawner.h"


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
	GetWorldTimerManager().ClearTimer(gameTimeHandle);

	//Check if there's need for harder difficulty
	if (check == 1 && houseSpawner->presentsDelivered >= firstCheckPresentScore)
	{
		houseSpawner->harderDifficulty(EASY);
		//setTimer(firstTimeCheck);
	}
	else if (check == 2 && houseSpawner->presentsDelivered >= secondCheckPresentScore) 
	{
		houseSpawner->harderDifficulty(MEDIUM);
		setTimer(firstTimeCheck);
	}
	else if (check == 3 && houseSpawner->presentsDelivered >= thirdCheckPresentScore) 
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

