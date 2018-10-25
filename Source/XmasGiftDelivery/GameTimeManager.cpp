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

	GetWorld()->GetTimerManager().SetTimer(gameTimeHandle, this, &AGameTimeManager::checkTime, firstTimeCheck, false);
}

// Called every frame
void AGameTimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UFUNCTION()
void AGameTimeManager::checkTime()
{
	houseSpawner->harderDifficulty(HARD);

	GetWorldTimerManager().ClearTimer(gameTimeHandle);
}

