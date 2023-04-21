// Fill out your copyright notice in the Description page of Project Settings.


#include "Coaster.h"
#include "Components/BoxComponent.h"

// Sets default values
ACoaster::ACoaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);

	staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMeshComp"));
	staticMeshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACoaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

