// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalFSM.h"

// Sets default values for this component's properties
UOldPalFSM::UOldPalFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOldPalFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOldPalFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UOldPalFSM::SetOrderCoctail()
{
}

void UOldPalFSM::SetState(EOldPalState next)
{
}

void UOldPalFSM::SetSitState(EOldPalSitState next)
{
}

void UOldPalFSM::SetDrinkState(EOldPalDrinkState next)
{
}

void UOldPalFSM::VisibleOrder()
{
}

void UOldPalFSM::AttachCustomer()
{
}

void UOldPalFSM::DetachCustomer()
{
}

// 랜덤 함수
int32 UOldPalFSM::SetRandRange(int32 idxStart, int32 idxEnd)
{
	int32 result = FMath::RandRange(idxStart, idxEnd);

	return result;
}
