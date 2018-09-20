// Fill out your copyright notice in the Description page of Project Settings.

#include "HouseSpawner.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
AHouseSpawner::AHouseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentTime = 0.0f;

	spawnRotation.ZeroRotator;
	spawnLocation.X = 0.0f;
	spawnLocation.Y = 0.0f;
	spawnLocation.Z = 0.0f;
}

// Called when the game starts or when spawned
void AHouseSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHouseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime = currentTime + 1 * DeltaTime;

	if (currentTime >= timerTime)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;

		//Spawn the object
		AHouseParent* newObject = GetWorld()->SpawnActor<AHouseParent>(spawnableObject, spawnLocation, spawnRotation, spawnParams);

		currentTime = 0.0f;
	}

}

