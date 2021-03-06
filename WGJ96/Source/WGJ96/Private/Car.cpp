// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ACar::ACar()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMesh->SetSimulatePhysics(true);
	CarMesh->SetNotifyRigidBodyCollision(true); // Simulation generates hit events
	RootComponent = CarMesh;

	auto RandNum = FMath::FRandRange(0.f, 1.0f);

	if (RandNum <= 0.1) { CarClass = ECarEnum::CE_Truck; }
	else if (RandNum <= 0.25) { CarClass = ECarEnum::CE_Bus; }
	else { CarClass = ECarEnum::CE_Car; }

	UE_LOG(LogTemp, Warning, TEXT("Random float: %f"), RandNum);

	// Set up variables for each car type
	switch (CarClass)
	{
	case ECarEnum::CE_Car:
		MaxSpeed = 800;
		Acceleration = 1000;
		break;
	case ECarEnum::CE_Bus:
		MaxSpeed = 600;
		Acceleration = 800;
		break;
	case ECarEnum::CE_Truck:
		MaxSpeed = 400;
		Acceleration = 600;
		StopDistance = 120;
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
	if (!bIsCrashed) 
	{
		CheckForStop();
		if (!Stop)
		{
			Accelerate(DeltaTime);
		}
		else
		{
			Decelerate(DeltaTime);
		}
	}
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACar::Accelerate(float DeltaTime)
{
	if (!CarMesh) { return; } // Pointer protection
	if(FMath::Abs<float>(CarMesh->GetComponentVelocity().GetMax()) < MaxSpeed)
	{
		CarMesh->AddImpulse(HeadingVector * Acceleration * DeltaTime, NAME_None, true);

		float VelocityFloat = CarMesh->GetComponentVelocity().Size();
		VelocityFloat = FMath::Clamp<float>(VelocityFloat, 0.f, MaxSpeed);

		CarMesh->SetPhysicsLinearVelocity(FVector(VelocityFloat) * HeadingVector );
	}

}


void ACar::Decelerate(float DeltaTime)
{
	if (!CarMesh) { return; } // Pointer protection
	if (CarMesh->GetComponentVelocity().Size() > CreepSpeed)
	{
		CarMesh->AddImpulse(HeadingVector * Braking * DeltaTime * FVector(-1), NAME_None, true);

		float VelocityFloat = CarMesh->GetComponentVelocity().Size();
		VelocityFloat = FMath::Clamp<float>(VelocityFloat, 0.f, MaxSpeed);

		CarMesh->SetPhysicsLinearVelocity(FVector(VelocityFloat) * HeadingVector);
	} 
	else
	{
		FHitResult OutHit = LineTrace();
		if (OutHit.GetActor()) // if we actually hit something
		{
			auto Distance = FVector::Dist(OutHit.ImpactPoint, GetActorLocation());
			Creep(DeltaTime, Distance);
		}
	}
}

void ACar::Creep(float DeltaTime, float Distance)
{
	auto AdjustedCreepSpeed = FMath::Clamp<float>(CreepSpeed, 0.001f, Distance - StopDistance);
	auto VelocityToSet = HeadingVector * FVector(AdjustedCreepSpeed);

	CarMesh->SetPhysicsLinearVelocity(VelocityToSet);
}

void ACar::CheckForStop()
{
	// Line-trace and see if there's a car or light in front of us
	FHitResult OutHit = LineTrace();
	if (OutHit.GetActor())
	{
		FVector CarVector = FVector(0);
		auto CarInFront = Cast<ACar>(OutHit.GetActor());
		//OutHit.GetActor()->GetDistanceTo(this);
		if (CarInFront) // If we hit a car with LineTrace
		{
			CarVector = CarInFront->GetHeadingVector();
			if (!CarVector.Equals(HeadingVector, 0.01) || CarInFront->GetIsCrashed())
			{
				Stop = false; 
			}
			else 
			{
				Stop = true; // Stop if car is headed in the same direction as this
			}
		}
		else 
		{
			Stop = true; // Stop anyway if there's something (not a car) in front of us
		}
	}
	else { Stop = false; } // Don't stop if nothing is hit by LineTrace
}

void ACar::Crash()
{
	if (!bIsCrashed) 
	{
		float ImpDirection = -1;
		if (FMath::RandBool()) { ImpDirection = FMath::Abs<float>(ImpDirection); } // Randomize where to apply force

		auto Impulse = GetActorRightVector() * ImpDirection * FVector(CrashForce);
		auto ImpLocation = GetActorLocation() + (HeadingVector * FVector(15) * ImpDirection);
		CarMesh->AddImpulseAtLocation(Impulse, ImpLocation);
		// Add up vector to make them roll over
		CarMesh->AddImpulseAtLocation(GetActorUpVector() * (FVector(CrashForce) * 0.6), ImpLocation);

		bIsCrashed = true;
	}
}

// TODO add delegate
void ACar::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

FHitResult ACar::LineTrace()
{
	FHitResult OutHit;
	auto Start = GetActorLocation() + GetActorRotation().Vector();
	auto End = Start + (GetActorForwardVector() * TraceDistance);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_PhysicsBody, CollisionParams);
	return OutHit;
}

FVector ACar::GetHeadingVector()
{	return HeadingVector;	}

bool ACar::GetIsCrashed()
{	return bIsCrashed;	}

void ACar::SetIsCounted(bool bToSet)
{	bIsCounted = bToSet;	}

void ACar::ModifyMaxSpeed(float SpeedModifier)
{	
	if (!bIsSpeedModified) 
	{
		MaxSpeed = MaxSpeed * SpeedModifier;
		bIsSpeedModified = true;
	}
}

bool ACar::GetIsCounted()
{	return bIsCounted;	}

ECarEnum ACar::GetCarClass()
{	return CarClass;	}
