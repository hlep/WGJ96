// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadGrid.generated.h"

class ARoadPart;

USTRUCT(BlueprintType)
struct FRoadArrayRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
	TArray<ARoadPart*> Cols;

	FRoadArrayRow() {}
};

USTRUCT(BlueprintType)
struct FRoadArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Array")
	TArray<FRoadArrayRow> Rows;

	FRoadArray() {}
};

UCLASS()
class WGJ96_API ARoadGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	FRoadArray RoadArray;

};
