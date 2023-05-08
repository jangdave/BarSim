// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerAnimInstance.h"
#include "CustomerCharacter.h"
#include "CustomerFSM.h"

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

void UCustomerAnimInstance::EndHoldCup()
{
	owner->customerFSM->SetSitState(ECustomerSitState::DRINK);
}

void UCustomerAnimInstance::EndDrinking()
{
	//owner->customerFSM->SetSitState(ECustomerSitState::JUDGEMENT);
}

void UCustomerAnimInstance::EndBad()
{
	//owner->customerFSM->SetState(ECustomerState::LEAVE);
}

void UCustomerAnimInstance::EndGood()
{
	//owner->customerFSM->SetState(ECustomerState::LEAVE);
}

//-------------------------------------------------------------------------------------drink
void UCustomerAnimInstance::OnDrinkAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerDrinkMontageFactory, 1, sectionName);
}


