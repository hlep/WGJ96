// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadPart.h"

// Sets default values
ARoadPart::ARoadPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->OnClicked.AddDynamic(this, &ARoadPart::BlockClicked);

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

void ARoadPart::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{

}

