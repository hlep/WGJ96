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

	UFUNCTION(BlueprintCallable)
	void SetIsCounted(bool bToSet);

	UFUNCTION(BlueprintCallable)
	void ModifyMaxSpeed(float SpeedToSet);

	UFUNCTION(BlueprintCallable)
		bool GetIsCounted();

	UFUNCTION(BlueprintCallable)
		ECarEnum GetCarClass();

	FVector GetHeadingVector();

	bool GetIsCrashed();

protected:

	UFUNCTION(BlueprintCallable)
	void Accelerate(float DeltaTime);

	UFUNCTION(BlueprintCallable) //TODO Check if it needs to be BPCallable
	void Decelerate(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void Creep(float DeltaTime, float Distance);

	UFUNCTION(BlueprintCallable)
	void Crash();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup") // TODO make ReadOnly
	ECarEnum CarClass = ECarEnum::CE_Car;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup") // TODO make ReadOnly
	float MaxSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Acceleration = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float Braking = 1200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float CreepSpeed = 100;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	bool bIsCounted = false;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	bool Stop = false;

private:

	void CheckForStop();

	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FHitResult LineTrace();

	// Unit vector where the car is headed
	FVector HeadingVector = FVector(0);

	float TraceDistance = 350.f;

	float StopDistance = 80.f;

	float CrashForce = 4500.f;

	bool bIsCrashed = false;

	bool bIsSpeedModified = false;

};
