// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerFSM.h"
#include "AIController.h"
#include "BarPlayer.h"
#include "CustomerAnimInstance.h"
#include "CustomerCharacter.h"
#include "CustomerOrderWidget.h"
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

	// 기본 상태 설정
	state = ECustomerState::IDLE;

	sitState = ECustomerSitState::STANDBY;

	drinkState = ECustomerDrinkState::IDLE;

	// 걷기 속도 조절
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
	case ECustomerState::READYSIT:
		TickReadySit();
		break;
	case ECustomerState::SIT:
		TickSit();
		break;
	case ECustomerState::LEAVE:
		TickLeave();
		break;
	}
}

// 손님 의자에 attach
void UCustomerFSM::AttachCustomer()
{
	owner->AttachToComponent(spawnManager->aChairs[idx]->sitComp, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// 손님 의자에 detach
void UCustomerFSM::DetachCustomer()
{
	owner->DetachAllSceneComponents(spawnManager->aChairs[idx]->sitComp, FDetachmentTransformRules::KeepWorldTransform);
}

// ------------------------------------------------------------------------------------idle state
// 상태 설정 함수
void UCustomerFSM::SetState(ECustomerState next)
{
	state = next;

	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;

	// 상태를 anim 클래스에 동기화
	owner->customerAnim->ownerState = next;
}

void UCustomerFSM::TickIdle()
{
	if(spawnManager != nullptr)
	{
		for(int i = 0; i<spawnManager->bIsSit.Num(); i++)
		{
			// 스폰 매니저에 있는 의자 배열에 착석 여부를 확인하는 배열 체크
			if(spawnManager->bIsSit[i] == false)
			{
				// 비어 있는 의자가 있으면 의자의 순서를 저장하고 다음 단계로
				idx = i;

				SetState(ECustomerState::MOVE);
			}
		}
	}
}

void UCustomerFSM::TickMove()
{
	// 지정 된 의자 뒤로 이동
	auto loc = spawnManager->chairs[idx]->GetActorLocation() + spawnManager->chairs[idx]->GetActorForwardVector() * -100;

	auto result = ai->MoveToLocation(loc);

	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		// 도착하면 다음 단계로
		SetState(ECustomerState::READYSIT);
	}
}

void UCustomerFSM::TickReadySit()
{
	// 지정 된 의자 뒤로 이동
	auto loc = spawnManager->chairs[idx]->GetActorLocation() + spawnManager->chairs[idx]->GetActorForwardVector() * -20;

	auto result = ai->MoveToLocation(loc);

	// 앉은 의자 배열에 착석 여부 바꾸기
	spawnManager->bIsSit[idx] = true;

	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		if(bCheckPlayAnim != true)
		{
			// 도착하면 앉는 애니메이션 실행
			bCheckPlayAnim = true;
		
			owner->customerAnim->OnStandAnim(TEXT("SitStoll"));
		}
	}
}

void UCustomerFSM::TickSit()
{
	// 대기시간 체크를 위한 시간 적립
	curTime += GetWorld()->GetDeltaSeconds();

	switch (sitState)
	{
	case ECustomerSitState::STANDBY:
		TickStandby();
		break;
	case ECustomerSitState::STANDBYWAITLONG:
		TickStandbyWaitLong();
		break;
	case ECustomerSitState::ORDER:
		TickOrder();
		break;
	case ECustomerSitState::WAIT:
		TickWait();
		break;
	case ECustomerSitState::WAITLONG:
		TickWaitLong();
		break;
	case ECustomerSitState::ORDERJUDGE:
		TickOrderJudge();
		break;
	case ECustomerSitState::HOLDCUP:
		TickHoldCup();
		break;
	case ECustomerSitState::DRINK:
		TickDrink();
		break;
	case ECustomerSitState::TASTEJUDGE:
		TickTasteJudge();
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
	// 문 밖의 스폰매니저 주변으로 이동
	auto loc = spawnManager->GetActorLocation() + spawnManager->GetActorRightVector() * 500;

	auto result = ai->MoveToLocation(loc);
	
	if(result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		// 도착하면 의자 배열에 착석 여부 바꾸고 사라짐
		spawnManager->bIsSit[idx] = false;
		
		owner->Destroy();
	}
}

// -----------------------------------------------------------------------------------------sit
// sit 상태 설정 함수
void UCustomerFSM::SetSitState(ECustomerSitState next)
{
	sitState = next;

	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;

	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;

	// 상태를 anim 클래스에 동기화
	owner->customerAnim->ownerSitState = next;
}

void UCustomerFSM::TickStandby()
{
	// 오더 위젯에 물음표 띄우기
	owner->order_UI->SetVisibility(ESlateVisibility::Visible);

	owner->order_UI->SetImage(owner->order_UI->orderImage[0]);

	// 일정 시간 전에 코스터가 있다면 오더로 상태 변경
	if(curTime < 10 && spawnManager->bIsCoaster[idx] != false)
	{
		SetSitState(ECustomerSitState::ORDER);
	}
	// 일정 시간 이후에 코스터가 없다면 웨이트롱으로 상태 변경
	else if(curTime >= 10 && spawnManager->bIsCoaster[idx] != true)
	{
		SetSitState(ECustomerSitState::STANDBYWAITLONG);
	}
}

void UCustomerFSM::TickStandbyWaitLong()
{
	// 오랜 기다림 불만을 표출하는 애니메이션 실행
	if(bCheckPlayAnim != true && curTime > 5)
	{
		bCheckPlayAnim = true;
		
		int32 temp = SetRandRange(0, 1);

		// 랜덤으로 두가지 애니메이션 중에 하나 실행
		if(temp == 0)
		{
			owner->customerAnim->OnSitAnim(TEXT("WaitLong1"));
		}
		else if(temp == 1)
		{
			owner->customerAnim->OnSitAnim(TEXT("WaitLong2"));
		}
	}
	// 코스터가 있으면
	else if(spawnManager->bIsCoaster[idx] != false)
	{
		SetSitState(ECustomerSitState::ORDER);
	}
}

void UCustomerFSM::TickOrder()
{
	if(bCheckPlayAnim != true)
	{
		bCheckPlayAnim = true;

		// 주문하는 애니메이션 실행
		owner->customerAnim->OnSitAnim(TEXT("Order"));

		// 랜덤으로 메뉴 선정
		int32 result = FMath::RandRange(1,8);
		
		if(result > 6)
		{
			// 진라임
			orderIdx = 1;
			
			owner->order_UI->SetImage(owner->order_UI->orderImage[orderIdx]);
		}
		else if(result <= 6 && result > 4)
		{
			// 다이키리
			orderIdx = 2;
			
			owner->order_UI->SetImage(owner->order_UI->orderImage[orderIdx]);
		}
		else if(result <= 4 && result > 2)
		{
			// 마타니
			orderIdx = 3;
			
			owner->order_UI->SetImage(owner->order_UI->orderImage[orderIdx]);
		}
		else if(result <= 2)
		{
			// 올드팔
			orderIdx = 4;
			
			owner->order_UI->SetImage(owner->order_UI->orderImage[orderIdx]);
		}
	}
	else
	{
		VisibleOrder();
	}
}

void UCustomerFSM::TickWait()
{
	VisibleOrder();

	// 일정 시간안에 코스터와 칵테일이 준비 되면 상태 이동
	if(curTime < 10 && spawnManager->bIsCoaster[idx] != false && spawnManager->bIsCoctail[idx] != false)
	{
		SetSitState(ECustomerSitState::ORDERJUDGE);

		owner->order_UI->SetVisibility(ESlateVisibility::Hidden);
	}
	// 그렇지 않다면 불만표시로 상태 이동
	else
	{
		SetSitState(ECustomerSitState::WAITLONG);
	}
}

void UCustomerFSM::TickWaitLong()
{
	VisibleOrder();

	// 오랜 기다림 불만을 표출하는 애니메이션 실행
	if(bCheckPlayAnim != true && curTime > 5)
	{
		bCheckPlayAnim = true;
		
		int32 temp = SetRandRange(0, 1);

		// 랜덤으로 두가지 애니메이션 중에 하나 실행
		if(temp == 0)
		{
			owner->customerAnim->OnSitAnim(TEXT("WaitLong1"));
		}
		else if(temp == 1)
		{
			owner->customerAnim->OnSitAnim(TEXT("WaitLong2"));
		}
	}
	// 코스터와 칵테일이 준비 되면 상태 이동
	else if(spawnManager->bIsCoaster[idx] != false && spawnManager->bIsCoctail[idx] != false)
	{
		SetSitState(ECustomerSitState::ORDERJUDGE);

		owner->order_UI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCustomerFSM::TickOrderJudge()
{
	// 주문과 일치하면 holdcup으로 상태 이동

	// 주문과 일치 하지 않으면 angry으로 상태 이동
}

void UCustomerFSM::TickHoldCup()
{
	if(bCheckPlayAnim != true && curTime > 1)
	{
		bCheckPlayAnim = true;

		// 컵을 잡는 애니메이션 실행
		owner->customerAnim->OnSitAnim(TEXT("HoldCup"));
	}
}

void UCustomerFSM::TickDrink()
{
	switch (drinkState)
	{
	case ECustomerDrinkState::IDLE:
		TickIdleCup();
		break;
	case ECustomerDrinkState::DRINK:
		TickDrink();
		break;
	case ECustomerDrinkState::UNHOLDCUP:
		TickUnHoldCup();
		break;
	}
}

void UCustomerFSM::TickTasteJudge()
{
	// score 가리기
	spawnManager->aChairs[idx]->HideScore();
	
	// 점수 판단
	auto result = spawnManager->aChairs[idx]->totalScore;

	if(result > 60)
	{
		SetSitState(ECustomerSitState::AWESOME);
	}
	else
	{
		SetSitState(ECustomerSitState::ANGRY);
	}
}

void UCustomerFSM::TickAngry()
{
	if(bCheckPlayAnim != true)
	{
		bCheckPlayAnim = true;
		
		owner->customerAnim->OnSitAnim(TEXT("TasteBad"));
	}
}

void UCustomerFSM::TickAwesome()
{
	if(bCheckPlayAnim != true)
	{
		bCheckPlayAnim = true;
		
		owner->customerAnim->OnSitAnim(TEXT("TasteGood"));
	}
}

// -----------------------------------------------------------------------------------------drink
// drink 상태 설정 함수
void UCustomerFSM::SetDrinkState(ECustomerDrinkState next)
{
	drinkState = next;

	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;

	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;
}

void UCustomerFSM::TickIdleCup()
{
	if(curTime > 1 && bCheckPlayAnim != true)
	{
		bCheckPlayAnim = true;
		
		owner->customerAnim->OnDrinkAnim(TEXT("Cheers"));
	}
}

void UCustomerFSM::TickDrinkCup()
{
	
}

void UCustomerFSM::TickUnHoldCup()
{
	
}

// 오더위젯 보이게 하는 함수
void UCustomerFSM::VisibleOrder()
{
	if(spawnManager->bIsPlayer[idx] != false)
	{
		// 플레이어가 근처에 있으면 주문한 칵테일 보여주기
		owner->order_UI->SetImage(owner->order_UI->orderImage[orderIdx]);
	}
	else
	{
		// 플레이어가 근터에 없으면 물음표
		owner->order_UI->SetImage(owner->order_UI->orderImage[0]);
	}
}

// 랜덤 함수
int32 UCustomerFSM::SetRandRange(int32 idxStart, int32 idxEnd)
{
	int32 result = FMath::RandRange(idxStart, idxEnd);

	return result;
}