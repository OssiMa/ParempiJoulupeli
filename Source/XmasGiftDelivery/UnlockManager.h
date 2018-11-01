// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		float today;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int lastUnlockedDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presents delivered")
		int presentScore;
};
