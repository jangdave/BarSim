// Fill out your copyright notice in the Description page of Project Settings.


#include "BarGameInstance.h"
#include "GameStartManager.h"
#include "Kismet/GameplayStatics.h"

void UBarGameInstance::Init()
{
	Super::Init();

	startManager = Cast<AGameStartManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameStartManager::StaticClass()));

	BindFunction();
}

void UBarGameInstance::CheckDay()
{
	// 메인맵으로 넘어 갈때마다 1씩 올라가게 한다
	if(bCheckGameMode != false)
	{
		checkDayCount++;
	}
}

void UBarGameInstance::BindFunction()
{
	goToMainMapDele.BindUFunction(this, FName("CheckDay"));
}
