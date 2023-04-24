// Fill out your copyright notice in the Description page of Project Settings.


#include "DropBase.h"

#include "Components/SphereComponent.h"

// Sets default values
ADropBase::ADropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	sphereComp->SetSphereRadius(1.0f);
	SetRootComponent(sphereComp);
	sphereComp->SetSimulatePhysics(true);
	sphereComp->SetCollisionProfileName(FName("Fluid"));
}

// Called when the game starts or when spawned
void ADropBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

