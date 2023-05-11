// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalAnimInstance.h"
#include "OldPalCharacter.h"

void UOldPalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UOldPalAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	owner = Cast<AOldPalCharacter>(TryGetPawnOwner());

	if(owner == nullptr)
	{
		return;
	}

	FVector velocity = owner->GetVelocity();
	FVector forVelocity = owner->GetActorForwardVector();
	forwardVelocity = FVector::DotProduct(velocity, forVelocity);
}

void UOldPalAnimInstance::OnStandAnim(float sectionTime)
{
	owner->bodyComp->GetAnimInstance()->Montage_Play(oldPalMontageFactory, 1, EMontagePlayReturnType::MontageLength, sectionTime);
}

void UOldPalAnimInstance::EndLean()
{
	owner->oldPalFSM->SetState(EOldPalState::TALK);
}

void UOldPalAnimInstance::EndSitStoll()
{
	owner->oldPalFSM->SetState(EOldPalState::SIT);

	owner->oldPalFSM->AttachCustomer();
}

void UOldPalAnimInstance::OnLeanAnim(float sectionTime)
{
	owner->bodyComp->GetAnimInstance()->Montage_Play(oldPalLeanMontageFactory, 1, EMontagePlayReturnType::MontageLength, sectionTime);
}

void UOldPalAnimInstance::EndTalk()
{
	OnLeanAnim(0);
}

void UOldPalAnimInstance::EndUnLean()
{
	owner->oldPalFSM->SetState(EOldPalState::READYMOVE);
}

void UOldPalAnimInstance::OnSitAnim(float sectionTime)
{
	owner->bodyComp->GetAnimInstance()->Montage_Play(oldPalSitMontageFactory, 1, EMontagePlayReturnType::MontageLength, sectionTime);
}

void UOldPalAnimInstance::OnDrinkAnim(float sectionTime)
{
	owner->bodyComp->GetAnimInstance()->Montage_Play(oldPalDrinkMontageFactory, 1, EMontagePlayReturnType::MontageLength, sectionTime);
}
