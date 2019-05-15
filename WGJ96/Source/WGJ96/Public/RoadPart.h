// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadPart.generated.h"

class ACar;

UCLASS()
class WGJ96_API ARoadPart : public AActor
{
	GENERATED_BODY()

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RoadMesh;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SpawnLocation;
	
public:	
	// Sets default values for this actor's properties
	ARoadPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float RoadLength = 254.f; // Length of one static mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpawnSpeed = 3.f;

private:

};
