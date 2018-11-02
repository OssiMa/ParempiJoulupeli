#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
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

	void CompareDays();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int day;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int month;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int year;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int lastCheckedDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int lastUnlockedDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presents delivered")
		int presentScore;
};
