// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	PawnMovement = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("PawnMovement"));

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMesh->SetupAttachment(DummyRoot);
	CarMesh->SetSimulatePhysics(true);

	// Set up variables for each car type
	switch (CarClass)
	{
	case ECarEnum::CE_Car:
		MaxSpeed = 300;
		break;
	case ECarEnum::CE_Bus:
		MaxSpeed = 200;
		break;
	case ECarEnum::CE_Truck:
		MaxSpeed = 150;
		break;
	default:
		break;
	}



}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

