#include "UnlockManager.h"
#include "OutputDeviceNull.h"


// Sets default values
AUnlockManager::AUnlockManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	dayCheck = 0;
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
	if (dayCheck <= 25)
	{
		if (presentScore >= scoreForUnlocking && day >= lastUnlockedDay)
		{
			SetUnlockedDay(1);
			dayCheck++;
		}
		else if (month < 12 && presentScore >= scoreForUnlocking)
		{
			SetUnlockedDay(1);
			dayCheck++;
		}

	}
}