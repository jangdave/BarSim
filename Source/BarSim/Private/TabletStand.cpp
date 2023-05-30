// Fill out your copyright notice in the Description page of Project Settings.


#include "TabletStand.h"

// Sets default values
ATabletStand::ATabletStand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
	meshComp->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void ATabletStand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATabletStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


