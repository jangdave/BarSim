// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalFSM.h"
#include "AIController.h"
#include "BarGameInstance.h"
#include "OldPalAnimInstance.h"
#include "OldPalCharacter.h"
#include "SpawnManager.h"
#include "StandPoint.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

	owner = Cast<AOldPalCharacter>(GetOwner());

	ai = Cast<AAIController>(owner->GetController());

	spawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));

	stand = Cast<AStandPoint>(UGameplayStatics::GetActorOfClass(GetWorld(), AStandPoint::StaticClass()));

	gi = Cast<UBarGameInstance>(GetWorld()->GetGameInstance());
	
	// 기본 상태 설정
	state = EOldPalState::IDLE;

	sitState = EOldPalSitState::STANDBY;

	drinkState = EOldPalDrinkState::IDLE;

	// 걷기 속도 조절
	owner->GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	// 주문 칵테일 정하기
	SetOrderCoctail();
}


// Called every frame
void UOldPalFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 대기시간 체크를 위한 시간 적립
	curTime += GetWorld()->GetDeltaSeconds();

	if(curTime > 20)
	{
		curTime = 0;
	}
	
	switch (state)
	{
	case EOldPalState::IDLE:
		TickIdle();
		break;
	case EOldPalState::READYLEAN:
		TickReadyLean();
		break;
	case EOldPalState::TALK:
		TickTalk();
		break;
	case EOldPalState::READYMOVE:
		TickReadyMove();
		break;
	case EOldPalState::MOVE:
		TickMove();
		break;
	case EOldPalState::READYSIT:
		TickReadySit();
		break;
	case EOldPalState::SIT:
		TickSit();
		break;
	case EOldPalState::LEAVE:
		TickLeave();
		break;
	}
}

// 손님 의자에 attach
void UOldPalFSM::AttachCustomer()
{
	owner->GetCapsuleComponent()->SetEnableGravity(false);
	
	owner->AttachToComponent(spawnManager->aChairs[idx]->sitComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// 손님 의자에 detach
void UOldPalFSM::DetachCustomer()
{
	owner->GetCapsuleComponent()->SetEnableGravity(true);
	
	owner->DetachAllSceneComponents(spawnManager->aChairs[idx]->sitComp, FDetachmentTransformRules::KeepWorldTransform);
}

// 주문 칵테일 정하기
void UOldPalFSM::SetOrderCoctail()
{
	if(gi != nullptr)
	{
		if(gi->checkDayCount == 3)
		{
			// 올드팔
			orderIdx = 4;
		}
	}
}

// -------------------------------------------------------------------------idle state
void UOldPalFSM::SetState(EOldPalState next)
{
	state = next;

	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;
	
	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;

	// 상태를 anim 클래스에 동기화
	owner->oldPalAnim->ownerState = next;
}

void UOldPalFSM::TickIdle()
{
	if(stand != nullptr)
	{
		auto loc = stand->GetActorLocation() - stand->GetActorForwardVector() * -100;

		auto result = ai->MoveToLocation(loc);

		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			SetState(EOldPalState::READYLEAN);
		}
	}
}

void UOldPalFSM::TickReadyLean()
{
	auto loc = stand->GetActorLocation();

	auto result = ai->MoveToLocation(loc);

	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		if(bCheckPlayAnim != true)
		{
			// 도착하면 기대는 애니메이션 실행
			bCheckPlayAnim = true;
		
			owner->oldPalAnim->OnStandAnim(1.34);
		}
	}
}

void UOldPalFSM::TickTalk()
{
	if(gi != nullptr)
	{
		if(gi->checkDayCount < 3)
		{
			if(bCheckPlayAnim != true)
			{
				// 도착하면 기대는 애니메이션 실행
				bCheckPlayAnim = true;
		
				owner->oldPalAnim->OnLeanAnim(1.01);
			}
		}
		else
		{
			if(bCheckPlayAnim != true)
			{
				// 도착하면 기대는 애니메이션 실행
				bCheckPlayAnim = true;
		
				owner->oldPalAnim->OnLeanAnim(2.68);
			}
		}
	}
}

void UOldPalFSM::TickReadyMove()
{
	if(spawnManager != nullptr)
	{
		for(int i = 0; i<spawnManager->bIsSit.Num(); i++)
		{
			// 스폰 매니저에 있는 의자 배열에 착석 여부를 확인하는 배열 체크
			if(spawnManager->bIsSit[i] == false)
			{
				// 비어 있는 의자가 있으면 의자의 순서를 저장하고
				idx = i;
				
				// 앉은 의자 배열에 착석 여부 바꾸기
				spawnManager->bIsSit[idx] = true;
				
				SetState(EOldPalState::MOVE);

				break;
			}
		}
	}
}

void UOldPalFSM::TickMove()
{
	// 지정 된 의자 뒤로 이동
	auto loc = spawnManager->chairs[idx]->GetActorLocation() + spawnManager->chairs[idx]->GetActorForwardVector() * -100;

	auto result = ai->MoveToLocation(loc);

	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		// 도착하면 다음 단계로
		SetState(EOldPalState::READYSIT);
	}
}

void UOldPalFSM::TickReadySit()
{
	// 지정 된 의자 뒤로 이동
	auto loc = spawnManager->chairs[idx]->GetActorLocation() + spawnManager->chairs[idx]->GetActorForwardVector() * -20;

	auto result = ai->MoveToLocation(loc);

	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		if(bCheckPlayAnim != true)
		{
			// 도착하면 앉는 애니메이션 실행
			bCheckPlayAnim = true;
		
			owner->oldPalAnim->OnStandAnim(0);
		}
	}
}

void UOldPalFSM::TickSit()
{
	switch (sitState)
	{
	case EOldPalSitState::STANDBY:
		TickStandby();
		break;
	case EOldPalSitState::STANDBYWAITLONG:
		TickStandbyWaitLong();
		break;
	case EOldPalSitState::ORDER:
		TickOrder();
		break;
	case EOldPalSitState::WAIT:
		TickWait();
		break;
	case EOldPalSitState::WAITLONG:
		TickWaitLong();
		break;
	case EOldPalSitState::ORDERJUDGE:
		TickOrderJudge();
		break;
	case EOldPalSitState::HOLDCUP:
		TickHoldCup();
		break;
	case EOldPalSitState::DRINK:
		TickDrink();
		break;
	case EOldPalSitState::TASTEJUDGE:
		TickTasteJudge();
		break;
	case EOldPalSitState::ANGRY:
		TickAngry();
		break;
	case EOldPalSitState::AWESOME:
		TickAwesome();
		break;
	case EOldPalSitState::READYLEAVE:
		TickReadyLeave();
		break;
	}
}

void UOldPalFSM::TickLeave()
{
	
}

// ---------------------------------------------------------------------------sit
// sit 상태 설정 함수
void UOldPalFSM::SetSitState(EOldPalSitState next)
{
	sitState = next;

	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;

	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;

	// 상태를 anim 클래스에 동기화
	owner->oldPalAnim->ownerSitState = next;
}

void UOldPalFSM::TickStandby()
{
	
}

void UOldPalFSM::TickStandbyWaitLong()
{
	
}

void UOldPalFSM::TickOrder()
{

}

void UOldPalFSM::TickWait()
{
	
}

void UOldPalFSM::TickWaitLong()
{
	
}

void UOldPalFSM::TickOrderJudge()
{
	
}

void UOldPalFSM::TickHoldCup()
{
	
}

void UOldPalFSM::TickDrink()
{
	
}

void UOldPalFSM::TickTasteJudge()
{
	
}

void UOldPalFSM::TickAngry()
{
	
}

void UOldPalFSM::TickAwesome()
{
	
}

void UOldPalFSM::TickReadyLeave()
{
	
}

void UOldPalFSM::SetDrinkState(EOldPalDrinkState next)
{
	
}

void UOldPalFSM::TickIdleCup()
{
}

void UOldPalFSM::TickDrinkCup()
{
}

void UOldPalFSM::TickUnHoldCup()
{
}

void UOldPalFSM::VisibleOrder()
{
	
}

// 랜덤 함수
int32 UOldPalFSM::SetRandRange(int32 idxStart, int32 idxEnd)
{
	int32 result = FMath::RandRange(idxStart, idxEnd);

	return result;
}
