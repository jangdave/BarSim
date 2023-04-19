// Fill out your copyright notice in the Description page of Project Settings.


#include "BarGameModeBase.h"

ABarGameModeBase::ABarGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABarGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABarGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
