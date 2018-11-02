#include "UnlockManager.h"


// Sets default values
AUnlockManager::AUnlockManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnlockManager::BeginPlay()
{
	Super::BeginPlay();

	day = FDateTime::Now().GetDay();
	month = FDateTime::Now().GetMonth();
	year = FDateTime::Now().GetYear();
}

// Called every frame
void AUnlockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnlockManager::CompareDays() 
{
	if (day && month && year >= lastCheckedDate) 
	{
		//Unlock stuff
	}
}

