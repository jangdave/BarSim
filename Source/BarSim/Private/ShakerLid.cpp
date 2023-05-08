// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakerLid.h"

// Sets default values
AShakerLid::AShakerLid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
	meshComp->SetSimulatePhysics(true);
	meshComp->SetCollisionProfileName(FName("Strainer"));
}

// Called when the game starts or when spawned
void AShakerLid::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShakerLid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

