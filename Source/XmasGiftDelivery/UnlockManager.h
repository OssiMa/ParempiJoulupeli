#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "GameFramework/GameModeBase.h"
#include "UnlockManager.generated.h"

UCLASS()
class XMASGIFTDELIVERY_API AUnlockManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUnlockManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Compare days and set unlocked days")
		void CompareDays();
	UFUNCTION(BlueprintImplementableEvent)
		void SetUnlockedDay(const int &dayCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int day;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int month;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int year;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int lastSavedMonth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int lastSavedYear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int lastUnlockedDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presents delivered")
		int presentScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presents delivered")
		int scoreForUnlocking;

	int dayCheck;
};
