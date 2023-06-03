// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfSlicedOrange.h"

// Sets default values
AHalfSlicedOrange::AHalfSlicedOrange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void AHalfSlicedOrange::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHalfSlicedOrange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

