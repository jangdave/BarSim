// Fill out your copyright notice in the Description page of Project Settings.


#include "Opener.h"

// Sets default values
AOpener::AOpener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	openerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("openerMesh"));
	SetRootComponent(openerMesh);
	openerMesh->SetRelativeScale3D(FVector(0.3f));

	
}

// Called when the game starts or when spawned
void AOpener::BeginPlay()
{
	Super::BeginPlay();

	openerMesh->SetSimulatePhysics(true);
}

// Called every frame
void AOpener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

