// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadPart.h"
#include "Car.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARoadPart::ARoadPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoadMesh0"));
	RootComponent = RoadMesh;

	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	SpawnLocation->SetupAttachment(RoadMesh);

}

// Called when the game starts or when spawned
void ARoadPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoadPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

