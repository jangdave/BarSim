// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerAnimInstance.h"
#include "CustomerCharacter.h"
#include "CustomerFSM.h"
#include "SpawnManager.h"

void UCustomerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UCustomerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	owner = Cast<ACustomerCharacter>(TryGetPawnOwner());

	if(owner == nullptr)
	{
		return;
	}

	FVector velocity = owner->GetVelocity();
	FVector forVelocity = owner->GetActorForwardVector();
	forwardVelocity = FVector::DotProduct(velocity, forVelocity);
}

//---------------------------------------------------------------------------------------stand
void UCustomerAnimInstance::OnStandAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerMontageFactory, 1, sectionName);
}

void UCustomerAnimInstance::EndSitStoll()
{
	owner->customerFSM->SetState(ECustomerState::SIT);
	
	owner->customerFSM->AttachCustomer();
}

//------------------------------------------------------------------------------------sit
void UCustomerAnimInstance::OnSitAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerSitMontageFactory, 1, sectionName);
}

void UCustomerAnimInstance::EndWaitLong()
{
	if(owner->customerFSM->sitState == ECustomerSitState::STANDBYWAITLONG)
	{
		owner->customerFSM->SetSitState(ECustomerSitState::STANDBYWAITLONG);
	}
	else
	{
		owner->customerFSM->SetSitState(ECustomerSitState::WAITLONG);
	}
}

void UCustomerAnimInstance::EndOrder()
{
	owner->customerFSM->SetSitState(ECustomerSitState::WAIT);
}

void UCustomerAnimInstance::AttachCup()
{
	owner->BindOverlap();
}

void UCustomerAnimInstance::EndHoldCup()
{
	owner->customerFSM->SetSitState(ECustomerSitState::DRINK);
}

void UCustomerAnimInstance::EndAngry()
{
	if(owner->customerFSM->spawnManager->aChairs[owner->customerFSM->idx]->bSameOrder == true)
	{
		owner->customerFSM->SetSitState(ECustomerSitState::READYLEAVE);
	}
	else if(owner->customerFSM->spawnManager->aChairs[owner->customerFSM->idx]->bUnSameOrder == true)
	{
		if(owner->customerFSM->bCheckOrder != true)
		{
			owner->customerFSM->SetSitState(ECustomerSitState::ORDERJUDGE);
		}
		else
		{
			owner->customerFSM->SetSitState(ECustomerSitState::READYLEAVE);
		}
	}
}

void UCustomerAnimInstance::EndGood()
{
	owner->customerFSM->SetSitState(ECustomerSitState::READYLEAVE);
}

void UCustomerAnimInstance::EndLeaveSit()
{
	owner->customerFSM->SetState(ECustomerState::LEAVE);
}

//-------------------------------------------------------------------------------------drink
void UCustomerAnimInstance::OnDrinkAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerDrinkMontageFactory, 1, sectionName);
}

void UCustomerAnimInstance::EndCheers()
{
	owner->customerFSM->SetDrinkState(ECustomerDrinkState::DRINK);
}

void UCustomerAnimInstance::EndDrinkAllLittle()
{
	owner->customerFSM->SetDrinkState(ECustomerDrinkState::DRINK);
}

void UCustomerAnimInstance::DetachCup()
{
	owner->DetachCup();
}

void UCustomerAnimInstance::EndUnHoldCup()
{
	owner->customerFSM->SetSitState(ECustomerSitState::TASTEJUDGE);
}


