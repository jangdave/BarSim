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

void UOldPalAnimInstance::OnSitAnim(FName sectionName)
{
	owner->PlayAnimMontage(oldPalMontageFactory, 1, sectionName);
}
