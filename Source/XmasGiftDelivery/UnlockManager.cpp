#include "UnlockManager.h"


// Sets default values
AUnlockManager::AUnlockManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	presentScorePloop = 21;
}

// Called when the game starts or when spawned
void AUnlockManager::BeginPlay()
{
	Super::BeginPlay();

	day = FDateTime::Now().GetDay();
	month = FDateTime::Now().GetMonth();
	year = FDateTime::Now().GetYear();

	SetUnlockedDay(presentScorePloop);
}

// Called every frame
void AUnlockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnlockManager::CompareDays() 
{
	if (presentScore >= scoreForUnlocking && day >= lastUnlockedDay)
	{
		FEditorScriptExecutionGuard ScriptGuard;

		//const FString command = FString::Printf(TEXT("SetUnlockedDayP"), daycount);
		FOutputDeviceNull ar;
		this->CallFunctionByNameWithArguments(TEXT("SetUnlockedDay"), ar, NULL, true);
	}
}


void AUnlockManager::SetUnlockedDay(int & dayCount) 
{
	//Do stuff here

	numberString = FString::SanitizeFloat(presentScorePloo);
	GEngine->AddOnScreenDebugMessage(-4, 2.f, FColor::Red, TEXT("Completed days is now ") + numberString);
}