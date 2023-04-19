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
	forwordVelocity = FVector::DotProduct(velocity, forVelocity);
}

void UCustomerAnimInstance::OnSitAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerSitMontageFactory, 1, sectionName);
}

void UCustomerAnimInstance::EndTalking()
{
	owner->costomerFSM->SetSitState(ECustomerSitState::WAITLONG);
}

void UCustomerAnimInstance::EndWaitLong()
{
	owner->costomerFSM->SetSitState(ECustomerSitState::WAITLONG);
}

void UCustomerAnimInstance::EndDrinking()
{
	owner->costomerFSM->SetSitState(ECustomerSitState::JUDGEMENT);
}

void UCustomerAnimInstance::EndBad()
{
	owner->costomerFSM->SetState(ECustomerState::LEAVE);
}

void UCustomerAnimInstance::EndGood()
{
	owner->costomerFSM->SetState(ECustomerState::LEAVE);
}
