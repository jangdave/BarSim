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
	owner->oldPalFSM->SetState(EOldPalState::CHOICE);
}

void UOldPalAnimInstance::EndUnLean()
{
	owner->oldPalFSM->SetState(EOldPalState::MOVE);
}

void UOldPalAnimInstance::OnSitAnim(float sectionTime)
{
	owner->bodyComp->GetAnimInstance()->Montage_Play(oldPalSitMontageFactory, 1, EMontagePlayReturnType::MontageLength, sectionTime);
}

void UOldPalAnimInstance::EndHoldCup()
{
	owner->oldPalFSM->SetSitState(EOldPalSitState::DRINK);
}

void UOldPalAnimInstance::AttachCup()
{
	owner->BindOldPalOverlap();
}

void UOldPalAnimInstance::OnDrinkAnim(float sectionTime)
{
	owner->bodyComp->GetAnimInstance()->Montage_Play(oldPalDrinkMontageFactory, 1, EMontagePlayReturnType::MontageLength, sectionTime);
}

void UOldPalAnimInstance::EndCheer()
{
	owner->oldPalFSM->SetDrinkState(EOldPalDrinkState::DRINK);
}

void UOldPalAnimInstance::EndDrinkLittle()
{
	owner->oldPalFSM->SetDrinkState(EOldPalDrinkState::DRINK);
}

void UOldPalAnimInstance::EndDrinkAll()
{
	owner->oldPalFSM->SetDrinkState(EOldPalDrinkState::UNHOLDCUP);
}

void UOldPalAnimInstance::DetachCup()
{
	owner->DetachCup();
}

void UOldPalAnimInstance::EndUnHoldCup()
{
	owner->oldPalFSM->SetSitState(EOldPalSitState::TASTEJUDGE);
}

void UOldPalAnimInstance::EndLeaveSit()
{
	owner->oldPalFSM->SetState(EOldPalState::LEAVE);
}
