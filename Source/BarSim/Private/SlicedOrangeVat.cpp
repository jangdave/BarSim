// Fill out your copyright notice in the Description page of Project Settings.


#include "SlicedOrangeVat.h"

// Sets default values
ASlicedOrangeVat::ASlicedOrangeVat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void ASlicedOrangeVat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlicedOrangeVat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

