// Fill out your copyright notice in the Description page of Project Settings.

#include "HouseParent.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"

// Sets default values
AHouseParent::AHouseParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	MyCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box component"));
	MyCollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionBox;

	MyCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHouseParent::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHouseParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHouseParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHouseParent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyOndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->ActorHasTag(TEXT("HouseTrigger")))) 
	{
		Destroy();
	}
}