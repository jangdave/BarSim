// Fill out your copyright notice in the Description page of Project Settings.


#include "OlivePick.h"

// Sets default values
AOlivePick::AOlivePick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	oliveComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("oliveComp"));
	SetRootComponent(oliveComp);
	oliveComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AOlivePick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOlivePick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

