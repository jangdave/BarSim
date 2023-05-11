// Fill out your copyright notice in the Description page of Project Settings.


#include "Strainer.h"

// Sets default values
AStrainer::AStrainer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetCollisionProfileName(FName("Strainer"));
	meshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AStrainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

