// Fill out your copyright notice in the Description page of Project Settings.


#include "IceCube.h"

#include "Components/BoxComponent.h"

// Sets default values
AIceCube::AIceCube(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	iceCubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("iceCubeMesh"));
	SetRootComponent(iceCubeMesh);
	iceCubeMesh->SetGenerateOverlapEvents(true);
	iceCubeMesh->SetSimulatePhysics(true);


	
}

// Called when the game starts or when spawned
void AIceCube::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIceCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

