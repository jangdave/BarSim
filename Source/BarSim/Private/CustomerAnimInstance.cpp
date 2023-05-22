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

	// 손님의 속도와 방향 변수로 값보내기
	FVector velocity = owner->GetVelocity();
	FVector forVelocity = owner->GetActorForwardVector();
	forwardVelocity = FVector::DotProduct(velocity, forVelocity);
}

//---------------------------------------------------------------------------------------stand
// 스탠드 몽타주 애니메이션 플레이 함수
void UCustomerAnimInstance::OnStandAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerMontageFactory, 1, sectionName);
}

// 스톨에 앉는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndSitStoll()
{
	// 손님 상태 변경
	owner->customerFSM->SetState(ECustomerState::SIT);

	// 손님 의자에 붙이기
	owner->customerFSM->AttachCustomer();
}

//------------------------------------------------------------------------------------sit
// 싯 몽타주 애니메이션 플레이 함수
void UCustomerAnimInstance::OnSitAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerSitMontageFactory, 1, sectionName);
}

// 기다리는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndWaitLong()
{
	// 손님이 주문받기 전이라면
	if(owner->customerFSM->sitState == ECustomerSitState::STANDBYWAITLONG)
	{
		owner->customerFSM->SetSitState(ECustomerSitState::STANDBYWAITLONG);
	}
	// 손님이 주문받은 이후라면
	else
	{
		owner->customerFSM->SetSitState(ECustomerSitState::WAITLONG);
	}
}

// 주문하는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndOrder()
{
	// 손님 상태 변경
	owner->customerFSM->SetSitState(ECustomerSitState::WAIT);
}

// 손님이 컵을 잡는 함수 연결
void UCustomerAnimInstance::AttachCup()
{
	owner->BindOverlap();
}

// 컵을 놓는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndHoldCup()
{
	// 손님 상태 변경
	owner->customerFSM->SetSitState(ECustomerSitState::DRINK);
}

// 화를 내는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndAngry()
{
	// 주문한 음료가 제대로 나왔을 경우
	if(owner->customerFSM->spawnManager->aChairs[owner->customerFSM->idx]->bSameOrder == true)
	{
		// 손님 상태 변경(자리에서 일어나게 하기)
		owner->customerFSM->SetSitState(ECustomerSitState::READYLEAVE);
	}
	// 주문한 음료가 제대로 안나왔을 경우
	else if(owner->customerFSM->spawnManager->aChairs[owner->customerFSM->idx]->bUnSameOrder == true)
	{
		// 한번 더 기회를 안줬다면
		if(owner->customerFSM->bCheckOrder != true)
		{
			// 손님 상태 변경
			owner->customerFSM->SetSitState(ECustomerSitState::ORDERJUDGE);
		}
		// 기회를 줬다면
		else
		{
			// 손님 상태 변경
			owner->customerFSM->SetSitState(ECustomerSitState::READYLEAVE);
		}
	}
}

// 칭찬하는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndGood()
{
	// 손님 상태 변경
	owner->customerFSM->SetSitState(ECustomerSitState::READYLEAVE);
}

// 자리에서 일어나는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndLeaveSit()
{
	// 손님 상태 변경
	owner->customerFSM->SetState(ECustomerState::LEAVE);
}

//-------------------------------------------------------------------------------------drink
// 드링크 몽타주 애니메이션 플레이 함수
void UCustomerAnimInstance::OnDrinkAnim(FName sectionName)
{
	owner->PlayAnimMontage(customerDrinkMontageFactory, 1, sectionName);
}

// 잔을 들고 치얼스 하는 애니메이션이 종료시 실행 함수
void UCustomerAnimInstance::EndCheers()
{
	// 손님 상태 변경
	owner->customerFSM->SetDrinkState(ECustomerDrinkState::DRINK);
}

// 칵테일을 마시는 애니메이션이 종료시 실행 함수
void UCustomerAnimInstance::EndDrinkAllLittle()
{
	// 손님 상태 변경
	owner->customerFSM->SetDrinkState(ECustomerDrinkState::DRINK);
}

// 손님이 컵을 놓는 함수 연결
void UCustomerAnimInstance::DetachCup()
{
	owner->DetachCup();
}

// 컵을 놓는 애니메이션 종료시 실행 함수
void UCustomerAnimInstance::EndUnHoldCup()
{
	// 손님 상태 변경
	owner->customerFSM->SetSitState(ECustomerSitState::TASTEJUDGE);
}


