// Fill out your copyright notice in the Description page of Project Settings.


#include "BarGameMode.h"
#include "BarGameInstance.h"

ABarGameMode::ABarGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABarGameMode::BeginPlay()
{
	Super::BeginPlay();

	gi = Cast<UBarGameInstance>(GetGameInstance());
}

void ABarGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ABarGameMode::SpawnMenu()
{
	
}
