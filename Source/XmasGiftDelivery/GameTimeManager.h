#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TimerManager.h"
#include "Engine.h"
#include "HouseSpawner.h"
#include "GameTimeManager.generated.h"

UCLASS()
class XMASGIFTDELIVERY_API AGameTimeManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameTimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void checkTime();

	UFUNCTION()
		void setTimer(float timeCheck);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HouseSpawnerReference")
		class AHouseSpawner* houseSpawner;

	FTimerHandle gameTimeHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time checks")
	float firstTimeCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time checks")
	float secondTimeCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time checks")
	float thirdTimeCheck;

	int check;
};
