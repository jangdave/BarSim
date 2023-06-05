// Fill out your copyright notice in the Description page of Project Settings.


#include "SlicedLimeVat.h"

// Sets default values
ASlicedLimeVat::ASlicedLimeVat(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void ASlicedLimeVat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlicedLimeVat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

