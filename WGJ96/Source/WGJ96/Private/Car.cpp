// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	//CarMesh->SetupAttachment(DummyRoot);
	CarMesh->SetSimulatePhysics(true);
	CarMesh->SetNotifyRigidBodyCollision(true);
	RootComponent = CarMesh;

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
	
	HeadingVector = GetActorForwardVector();
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Drive(DeltaTime);
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACar::Drive(float DeltaTime)
{
	auto CurrentVelocity = CarMesh->GetComponentVelocity();

	if(CurrentVelocity.GetMax() < MaxSpeed)
	{
		//auto VelocityToSet = (HeadingVector * (Acceleration * DeltaTime) + CurrentVelocity);
		//FMath::Clamp<float>(VelocityToSet.X, 0.f, MaxSpeed);
		//CarMesh->SetPhysicsLinearVelocity(VelocityToSet);

		CarMesh->AddImpulse(HeadingVector * Acceleration, NAME_None, true);
		//TODO Clamp velocity to MaxSpeed

	}
	auto Velocity = CarMesh->GetComponentVelocity();
	
	UE_LOG(LogTemp, Warning, TEXT("CurrentVelocity: %s"), *Velocity.ToCompactString());
}

