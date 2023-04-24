// Fill out your copyright notice in the Description page of Project Settings.


#include "IceCube.h"

#include "Components/BoxComponent.h"

// Sets default values
AIceCube::AIceCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(5.0f));
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	
	iceCubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("iceCubeMesh"));
	iceCubeMesh->SetupAttachment(boxComp);


	
}

// Called when the game starts or when spawned
void AIceCube::BeginPlay()
{
	Super::BeginPlay();


	boxComp->SetSimulatePhysics(true);
	boxComp->SetGenerateOverlapEvents(true);

	iceCubeMesh->SetGenerateOverlapEvents(false);
	iceCubeMesh->SetSimulatePhysics(false);

}

// Called every frame
void AIceCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

