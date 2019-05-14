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

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CarMesh;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnMovementComponent* PawnMovement;

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

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup") // TODO make ReadOnly
	ECarEnum CarClass = ECarEnum::CE_Car;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup") // TODO make ReadOnly
	float MaxSpeed = 300;

};