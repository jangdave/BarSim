// Fill out your copyright notice in the Description page of Project Settings.


#include "BarGameMode.h"
#include "MenuWidgetActor.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABarGameMode::ABarGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABarGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ABarGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void ABarGameMode::SpawnMenu()
{
	auto player = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
	
	if(player != nullptr)
	{
		FVector rot1 = player->VRReplicatedCamera->GetComponentLocation();
		FVector rot2 = player->VRReplicatedCamera->GetComponentLocation() + player->VRReplicatedCamera->GetForwardVector() * 80;
		FRotator rotend = UKismetMathLibrary::FindLookAtRotation(rot1, rot2);
		FRotator rot = {0, rotend.Yaw - 180, 0};
		FVector loc1 = player->VRReplicatedCamera->GetComponentLocation() + player->VRReplicatedCamera->GetForwardVector() * 80;
		FVector loc2 = player->GetActorLocation() + player->GetActorUpVector() * 30;
		FVector loc = {loc1.X, loc1.Y, loc2.Z};
		menuWidget = GetWorld()->SpawnActor<AMenuWidgetActor>(menuFactory, loc, rot);
	}
}

void ABarGameMode::DestroyMenu()
{
	if(menuWidget!=nullptr)
	{
		menuWidget->Destroy();
	}
}
