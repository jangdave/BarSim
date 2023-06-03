// Fill out your copyright notice in the Description page of Project Settings.


#include "SlicedOrange.h"

// Sets default values
ASlicedOrange::ASlicedOrange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void ASlicedOrange::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlicedOrange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

