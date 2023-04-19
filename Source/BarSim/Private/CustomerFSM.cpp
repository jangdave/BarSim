// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerFSM.h"
#include "AIController.h"
#include "BarPlayer.h"
#include "CustomerAnimInstance.h"
#include "CustomerCharacter.h"
#include "SpawnManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCustomerFSM::UCustomerFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomerFSM::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<ACustomerCharacter>(GetOwner());

	player = Cast<ABarPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ABarPlayer::StaticClass()));
	
	ai = Cast<AAIController>(owner->GetController());

	spawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	
	state = ECustomerState::IDLE;

	sitState =ECustomerSitState::ORDER;
	
	owner->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}


// Called every frame
void UCustomerFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (state)
	{
	case ECustomerState::IDLE:
		TickIdle();
		break;
	case ECustomerState::MOVE:
		TickMove();
		break;
	case ECustomerState::SIT:
		TickSit();
		break;
	case ECustomerState::LEAVE:
		TickLeave();
		break;
	}
}

// ------------------------------------------------------------------------------------idle state
void UCustomerFSM::SetState(ECustomerState next)
{
	state = next;
}

void UCustomerFSM::TickIdle()
{
	if(spawnManager != nullptr)
	{
		for(int i = 0; i<spawnManager->bIsSit.Num(); i++)
		{
			if(spawnManager->bIsSit[i] == false)
			{
				idx = i;

				SetState(ECustomerState::MOVE);
			}
		}
	}
}

void UCustomerFSM::TickMove()
{
	auto loc = spawnManager->chairs[idx]->GetActorLocation();

	auto result = ai->MoveToLocation(loc);

	spawnManager->bIsSit[idx] = true;
	
	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		SetState(ECustomerState::SIT);
	}
}

void UCustomerFSM::TickSit()
{
	curTime += GetWorld()->GetDeltaSeconds();

	switch (sitState)
	{
	case ECustomerSitState::ORDER:
		TickOrder();
		break;
	case ECustomerSitState::WAIT:
		TickWait();
		break;
	case ECustomerSitState::WAITLONG:
		TickWaitLong();
		break;
	case ECustomerSitState::DRINK:
		TickDrink();
		break;
	case ECustomerSitState::ANGRY:
		TickAngry();
		break;
	case ECustomerSitState::AWESOME:
		TickAwesome();
		break;
	}
}

void UCustomerFSM::TickLeave()
{
	auto loc = spawnManager->GetActorLocation() + spawnManager->GetActorRightVector() * 500;

	auto result = ai->MoveToLocation(loc);
	
	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		spawnManager->bIsSit[idx] = false;
		
		owner->Destroy();
	}
}

// -----------------------------------------------------------------------------------------sit
void UCustomerFSM::SetSitState(ECustomerSitState next)
{
	sitState = next;

	curTime = 0;

	bCheckPlayAnim = false;
}

void UCustomerFSM::TickOrder()
{
	FVector lookDist = player->GetActorLocation() - owner->GetActorLocation();

	FRotator lookRot = FRotationMatrix::MakeFromX(lookDist).Rotator();

	owner->SetActorRotation(FMath::Lerp(owner->GetActorRotation(), lookRot, 0.1f));
	
	if(curTime > 1)
	{		
		SetSitState(ECustomerSitState::WAIT);
	}
}

void UCustomerFSM::TickWait()
{
	if(curTime > 1 && bCheckPlayAnim != true)
	{
		bCheckPlayAnim = true;
		
		owner->customerAnim->OnSitAnim(TEXT("Talking"));
	}
	// 음료가 나오면
	//if()
	//{
		
	//}
}

void UCustomerFSM::TickWaitLong()
{
	if(curTime > 5 && bCheckPlayAnim != true)
	{
		bCheckPlayAnim = true;
		
		owner->customerAnim->OnSitAnim(TEXT("WaitLong"));
	}
	// 음료가 나오면
	//if()
	//{
		
	//}
}

void UCustomerFSM::TickDrink()
{
	
}

void UCustomerFSM::TickAngry()
{
	
}

void UCustomerFSM::TickAwesome()
{
	
}