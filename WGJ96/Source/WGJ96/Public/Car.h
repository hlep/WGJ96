// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Car.generated.h"

class UPawnMovementComponent;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECarEnum : uint8
{
	CE_Car		UMETA(DisplayName = "Car"),
	CE_Bus		UMETA(DisplayName = "Bus"),
	CE_Truck	UMETA(DisplayName = "Truck")
};


UCLASS()
class WGJ96_API ACar : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CarMesh;

public:
	// Sets default values for this pawn's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetHeadingVector();

protected:

	UFUNCTION(BlueprintCallable)
	void Drive(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup") // TODO make ReadOnly
	ECarEnum CarClass = ECarEnum::CE_Car;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup") // TODO make ReadOnly
	float MaxSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Acceleration = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Braking = 200;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	bool bIsCounted = false;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	bool Stop = false;

private:

	void CheckForStop();

	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Unit vector where the car is headed
	FVector HeadingVector = FVector(0);

	float StopDistance = 250.f;

};
