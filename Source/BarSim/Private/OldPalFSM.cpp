// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalFSM.h"
#include "AIController.h"
#include "BarGameInstance.h"
#include "OldPalAnimInstance.h"
#include "OldPalCharacter.h"
#include "OldPalOrderWidget.h"
#include "PlayerCharacter.h"
#include "PlayerDialogWidget.h"
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

	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
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
	case EOldPalState::CHOICE:
		TickChoice();
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

	owner->GetMesh()->SetRelativeLocation(FVector(0, 0, -5));
	
	owner->AttachToComponent(spawnManager->aChairs[idx]->sitOldComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// 손님 의자에 detach
void UOldPalFSM::DetachCustomer()
{
	owner->GetCapsuleComponent()->SetEnableGravity(true);

	//owner->GetMesh()->SetRelativeLocation(FVector(0, 0, 5));
	
	owner->DetachAllSceneComponents(spawnManager->aChairs[idx]->sitOldComp, FDetachmentTransformRules::KeepWorldTransform);
}

// 주문 칵테일 정하기
void UOldPalFSM::SetOrderCoctail()
{
	if(gi->checkDayCount == 3)
	{
		// 올드팔
		orderIdx = 4;
	}
}

// -------------------------------------------------------------------------idle
// idle 상태 설정 함수
void UOldPalFSM::SetState(EOldPalState next)
{
	state = next;

	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;
	
	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;

	// 상태를 anim 클래스에 동기화
	owner->oldPalAnim->ownerState = next;

	// 시간 초기화
	bCount = false;

	// 대화 초기화
	bPlayerTalk = false;

	bOldPalTalk = false;
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
		if(gi->checkDayCount == 1)
		{
			if(bPlayerTalk != true)
			{
				// 플레이어 대사 0
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(0);
				player->playerText_UI->StartPlayer();

				bPlayerTalk = true;
			}
			
			if(bCheckPlayAnim != true)
			{
				bCheckPlayAnim = true;
			
				// 도착하면 기대는 애니메이션 실행
				owner->oldPalAnim->OnStandAnim(2.01);
			}
		}
		else
		{
			//
		}
	}
}

void UOldPalFSM::TickTalk()
{
	if(gi->checkDayCount == 1)
	{
		if(bPlayerTalk != true && curTime > 1)
		{
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();

			bPlayerTalk = true;

			if(bOldPalTalk != true)
			{
				// 올드팔 대사 0
				owner->oldPal_UI->SetOldPalText(0);
				owner->oldPal_UI->StartOldPal();

				bOldPalTalk = true;
				
				if(bCheckPlayAnim != true)
				{
					bCheckPlayAnim = true;
			
					// 말하는 애니메이션 실행
					owner->oldPalAnim->OnLeanAnim(1.01);
				}		
			}
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickChoice()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = true;
		}
		
		if(bCheckPlayAnim != true && curTime > 3)
		{
			// 올드팔 대사 1
			owner->oldPal_UI->SetOldPalText(1);
			owner->oldPal_UI->StartOldPal();
			
			bCheckPlayAnim = true;
		
			// 말하는 애니메이션 실행
			owner->oldPalAnim->OnLeanAnim(4.51);
		}

		if(curTime > 5)
		{
			SetState(EOldPalState::READYMOVE);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickReadyMove()
{
	if(gi->checkDayCount == 1)
	{
		// 의자의 저장하고
		idx = 1;
		
		// 앉은 의자 배열에 착석 여부 바꾸기
		spawnManager->bIsSit[idx] = true;

		// 선택지 띄우기
		if(player->playerText_UI->choiceCount == 0)
		{
			if(bPlayerTalk != true && curTime > 1)
			{
				// 플레이어 초이스 1번째
				player->playerText_UI->SetSwitcher(1);
				player->playerText_UI->SetChoice1();
				player->playerText_UI->StartPlayer();

				bPlayerTalk = true;

				// 올드팔 대사 지우기
				if(bOldPalTalk != true)
				{
					owner->oldPal_UI->EndOldPal();

					bOldPalTalk = true;
				}
			}
		}
		// 선택 왼쪽
		else if(player->playerText_UI->choiceCount == 1)
		{
			if(bCount != true)
			{
				curTime = 0;

				bCount = true;
			}

			if(bPlayerTalk != false)
			{
				// 플레이어 초이스 지우기
				player->playerText_UI->EndPlayer();
				
				bPlayerTalk = false;
			}
			
			if(curTime > 1 && bCheckPlayAnim != true)
			{
				// 플레이어 대사 1
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(1);
				player->playerText_UI->StartPlayer();

				bCheckPlayAnim = true;
			
				// 다시 일어서는 애니메이션 실행
				owner->oldPalAnim->OnLeanAnim(0.01);
			}
		}
		// 선택 오른쪽
		else if(player->playerText_UI->choiceCount == 2)
		{
			if(bCount != true)
			{
				curTime = 0;

				bCount = true;
			}

			if(bPlayerTalk != false)
			{
				// 플레이어 초이스 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = false;
			}

			if(curTime > 1 && bCheckPlayAnim != true)
			{
				// 플레이어 대사 2
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(2);
				player->playerText_UI->StartPlayer();

				bCheckPlayAnim = true;
			
				// 다시 일어서는 애니메이션 실행
				owner->oldPalAnim->OnLeanAnim(0.01);
			}
		}
	}
	else
	{
		// 의자의 저장하고
		idx = 1;
		
		// 앉은 의자 배열에 착석 여부 바꾸기
		spawnManager->bIsSit[idx] = true;

		//
	}
}

void UOldPalFSM::TickMove()
{
	if(gi->checkDayCount == 1)
	{
		// 지정 된 의자 뒤로 이동
		auto loc = spawnManager->chairs[idx]->GetActorLocation() + spawnManager->chairs[idx]->GetActorForwardVector() * -100;

		auto result = ai->MoveToLocation(loc);
		
		if(bPlayerTalk != true && curTime > 1)
		{
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();

			bPlayerTalk = true;
		}
		
		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			
			// 도착하면 다음 단계로
			SetState(EOldPalState::READYSIT);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickReadySit()
{
	if(gi->checkDayCount == 1)
	{
		// 지정 된 의자 뒤로 이동
		auto loc = spawnManager->chairs[idx]->GetActorLocation() + spawnManager->chairs[idx]->GetActorForwardVector() * -10;
		auto result = ai->MoveToLocation(loc);

		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			if(bPlayerTalk != true)
			{
				// 플레이어 대사 3
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(3);
				player->playerText_UI->StartPlayer();

				bPlayerTalk = true;
			}
			
			if(bCheckPlayAnim != true)
			{
				// 도착하면 앉는 애니메이션 실행
				bCheckPlayAnim = true;

				owner->oldPalAnim->OnStandAnim(0.01);
			}
		}
	}
	else
	{
		//
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
	if(gi->checkDayCount == 1)
	{
		// 문 밖의 스폰매니저 주변으로 이동
		auto loc = spawnManager->GetActorLocation();

		auto result = ai->MoveToLocation(loc);

		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			owner->GetCharacterMovement()->MaxWalkSpeed = 0;
		}

		if(bPlayerTalk != true && curTime > 3)
		{
			// 플레이어 대사 5
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(5);
			player->playerText_UI->StartPlayer();
			
			bPlayerTalk = true;
		}

		if(bOldPalTalk != true && curTime > 5)
		{
			// 플레이어 대사 6
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(6);

			bOldPalTalk = true;
		}

		if(bCheckPlayAnim != true && curTime > 7)
		{
			// 플레이어 대사 7
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(7);

			bCheckPlayAnim = true;
		}

		if(curTime > 9)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "StartMap");
		}
	}
	else
	{
		
	}
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
	
	// 시간 초기화
	bCount = false;

	// 대화 초기화
	bPlayerTalk = false;

	bOldPalTalk = false;
}

void UOldPalFSM::TickStandby()
{
	if(gi->checkDayCount == 1)
	{
		if(bPlayerTalk != true && curTime > 2)
		{
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();

			bPlayerTalk = true;
		}

		if(bOldPalTalk != true && curTime > 3)
		{
			// 올드팔 대사 2
			owner->oldPal_UI->SetOldPalText(2);
			owner->oldPal_UI->StartOldPal();

			bOldPalTalk = true;
			
			if(bCheckPlayAnim != true)
			{
				// 토크2 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(5.01);
			}
		}
		
		// 일정 시간 전에 코스터가 있다면 오더로 상태 변경
		if(curTime > 6 && curTime <= 10 && spawnManager->bIsCoaster[idx] != false)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::ORDER);
		}
		// 일정 시간 이후에 코스터가 없다면 웨이트롱으로 상태 변경
		else if(curTime > 10)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::STANDBYWAITLONG);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickStandbyWaitLong()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			// 올드팔 대사 5
			owner->oldPal_UI->SetOldPalText(5);
			owner->oldPal_UI->StartOldPal();

			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크1 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(3.68);
			}
		}
		
		// 코스터가 있으면
		if(spawnManager->bIsCoaster[idx] != false)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::ORDER);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickOrder()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			// 올드팔 대사 3
			owner->oldPal_UI->SetOldPalText(3);
			owner->oldPal_UI->StartOldPal();

			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크0 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(0.01);
			}
		}

		if(curTime > 8)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::WAIT);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickWait()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 2)
		{
			// 올드팔 대사 4
			owner->oldPal_UI->SetOldPalText(4);
			owner->oldPal_UI->StartOldPal();
			
			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크2 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(5.01);
			}
		}
		
		// 일정 시간안에 코스터와 칵테일이 준비 되면 상태 이동
		if(curTime > 5 && curTime <= 10 && spawnManager->bIsCoaster[idx] != false && spawnManager->bIsCoctail[idx] != false)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::ORDERJUDGE);
		}
		// 그렇지 않다면 불만표시로 상태 이동
		else if(curTime > 10)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::WAITLONG);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickWaitLong()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			// 올드팔 대사 6
			owner->oldPal_UI->SetOldPalText(6);
			owner->oldPal_UI->StartOldPal();

			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크1 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(3.68);
			}
		}
		
		// 코스터와 칵테일이 준비 되면 상태 이동
		if(curTime > 2 && spawnManager->bIsCoaster[idx] != false && spawnManager->bIsCoctail[idx] != false)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			if(bPlayerTalk != true)
			{
				// 플레이어 대사 4
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(4);
				player->playerText_UI->StartPlayer();

				bPlayerTalk = true;
				
				SetSitState(EOldPalSitState::ORDERJUDGE);
			}
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickOrderJudge()
{
	if(gi->checkDayCount == 1)
	{
		// 진라임을 주면
		if(spawnManager->orderCoctailIdx[idx] == 1)
		{
			if(bPlayerTalk != true && curTime > 1)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				// 올드팔 대사 7
				owner->oldPal_UI->SetOldPalText(7);
				owner->oldPal_UI->StartOldPal();

				bOldPalTalk = true;

				if(bCheckPlayAnim != true)
				{
					// 토크0 애니메이션 실행
					bCheckPlayAnim = true;
			
					owner->oldPalAnim->OnSitAnim(0.01);
				}
			}

			if(curTime > 5)
			{
				SetSitState(EOldPalSitState::HOLDCUP);

				spawnManager->aChairs[idx]->HideScore();
				
				spawnManager->aChairs[idx]->MoveCup();
			}
		}
		// 다이커리를 주면
		else if(spawnManager->orderCoctailIdx[idx] == 2)
		{
			if(bPlayerTalk != true && curTime > 1)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				// 올드팔 대사 8
				owner->oldPal_UI->SetOldPalText(8);
				owner->oldPal_UI->StartOldPal();

				bOldPalTalk = true;

				if(bCheckPlayAnim != true)
				{
					// 토크0 애니메이션 실행
					bCheckPlayAnim = true;
			
					owner->oldPalAnim->OnSitAnim(0.01);
				}
			}

			if(curTime > 5)
			{
				SetSitState(EOldPalSitState::HOLDCUP);

				spawnManager->aChairs[idx]->HideScore();
				
				spawnManager->aChairs[idx]->MoveCup();
			}
		}
		// 마티니를 주면
		else if(spawnManager->orderCoctailIdx[idx] == 3)
		{
			if(bPlayerTalk != true && curTime > 1)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				// 올드팔 대사 9
				owner->oldPal_UI->SetOldPalText(9);
				owner->oldPal_UI->StartOldPal();

				bOldPalTalk = true;

				if(bCheckPlayAnim != true)
				{
					// 토크0 애니메이션 실행
					bCheckPlayAnim = true;
			
					owner->oldPalAnim->OnSitAnim(0.01);
				}
			}

			if(curTime > 5)
			{
				SetSitState(EOldPalSitState::HOLDCUP);

				spawnManager->aChairs[idx]->HideScore();
				
				spawnManager->aChairs[idx]->MoveCup();
			}
		}
		// 그이외 모든것
		else if(spawnManager->orderCoctailIdx[idx] == 5)
		{
			if(bPlayerTalk != true && curTime > 1)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				// 올드팔 대사 10
				owner->oldPal_UI->SetOldPalText(10);
				owner->oldPal_UI->StartOldPal();

				bOldPalTalk = true;

				if(bCheckPlayAnim != true)
				{
					// 토크0 애니메이션 실행
					bCheckPlayAnim = true;
			
					owner->oldPalAnim->OnSitAnim(0.01);
				}
			}

			if(curTime > 5)
			{
				SetSitState(EOldPalSitState::HOLDCUP);

				spawnManager->aChairs[idx]->MoveCup();
			}
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickHoldCup()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = true;
		}

		if(bCheckPlayAnim != true && curTime > 2)
		{
			bCheckPlayAnim = true;

			// 컵 잡는 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(6.34);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickDrink()
{
	switch (drinkState)
	{
	case EOldPalDrinkState::IDLE:
		TickIdleCup();
		break;
	case EOldPalDrinkState::DRINK:
		TickDrinkCup();
		break;
	case EOldPalDrinkState::UNHOLDCUP:
		TickUnHoldCup();
		break;
	}
}

void UOldPalFSM::TickTasteJudge()
{
	if(gi->checkDayCount == 1)
	{
		// 진라임 이였다면
		if(spawnManager->orderCoctailIdx[idx] == 1)
		{
			if(spawnManager->scoreIdx[0] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 12
				owner->oldPal_UI->SetOldPalText(12);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 13
				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 0 && spawnManager->scoreIdx[0] == 0 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 15
				owner->oldPal_UI->SetOldPalText(15);
				owner->oldPal_UI->StartOldPal();

				// 토크2 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(5.01);

				SetSitState(EOldPalSitState::ANGRY);
			}
		}
		// 다이커리 였다면
		else if(spawnManager->orderCoctailIdx[idx] == 2)
		{
			if(spawnManager->scoreIdx[2] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 14
				owner->oldPal_UI->SetOldPalText(14);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[0] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 12
				owner->oldPal_UI->SetOldPalText(12);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 13
				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[2] == 0 && spawnManager->scoreIdx[1] == 0 && spawnManager->scoreIdx[0] == 0 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 15
				owner->oldPal_UI->SetOldPalText(15);
				owner->oldPal_UI->StartOldPal();

				// 토크2 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(5.01);

				SetSitState(EOldPalSitState::ANGRY);
			}
		}
		// 마티니 였다면
		else if(spawnManager->orderCoctailIdx[idx] == 3)
		{
			if(spawnManager->scoreIdx[2] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 14
				owner->oldPal_UI->SetOldPalText(14);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[0] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 12
				owner->oldPal_UI->SetOldPalText(12);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 13
				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[2] == 0 && spawnManager->scoreIdx[1] == 0 && spawnManager->scoreIdx[0] == 0 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 15
				owner->oldPal_UI->SetOldPalText(15);
				owner->oldPal_UI->StartOldPal();

				// 토크2 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(5.01);

				SetSitState(EOldPalSitState::ANGRY);
			}
		}
		else if(spawnManager->orderCoctailIdx[idx] == 5)
		{
			if(bOldPalTalk != true)
			{
				bOldPalTalk = true;

				// 올드팔 대사 16
				owner->oldPal_UI->SetOldPalText(16);
				owner->oldPal_UI->StartOldPal();

				// 토크2 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(5.01);

				SetSitState(EOldPalSitState::ANGRY);
			}
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickAngry()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 2)
		{
			// 올드팔 대사 지우기
			bOldPalTalk = true;
			
			owner->oldPal_UI->EndOldPal();
		}

		if(bCheckPlayAnim != true && curTime > 4)
		{
			// 올드팔 대사 17
			owner->oldPal_UI->SetOldPalText(17);
			owner->oldPal_UI->StartOldPal();

			bCheckPlayAnim = true;

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);

			SetSitState(EOldPalSitState::AWESOME);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickAwesome()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 2)
		{
			// 올드팔 대사 지우기
			bOldPalTalk = true;
			
			owner->oldPal_UI->EndOldPal();
		}
		
		if(bCheckPlayAnim != true && curTime > 4)
		{
			// 올드팔 대사 18
			owner->oldPal_UI->SetOldPalText(18);
			owner->oldPal_UI->StartOldPal();

			bCheckPlayAnim = true;

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);

			SetSitState(EOldPalSitState::READYLEAVE);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickReadyLeave()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 2)
		{
			// 올드팔 대사 지우기
			bOldPalTalk = true;
			
			owner->oldPal_UI->EndOldPal();

			DetachCustomer();

			if(bCheckPlayAnim != true)
			{
				bCheckPlayAnim = true;

				// 자리에서 일어나는 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(10.58);
			}
		}
	}
	else
	{
		//
	}
}

// ---------------------------------------------------------------------------drink
// drink 상태 설정 함수
void UOldPalFSM::SetDrinkState(EOldPalDrinkState next)
{
	drinkState = next;

	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;

	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;

	// 시간 초기화
	bCount = false;

	// 대화 초기화
	bPlayerTalk = false;

	bOldPalTalk = false;
}

void UOldPalFSM::TickIdleCup()
{
	if(gi->checkDayCount == 1)
	{
		if(bCheckPlayAnim != true && curTime > 1)
		{
			bCheckPlayAnim = true;

			// 잔을 들고 cheers 애니메이션 실행
			owner->oldPalAnim->OnDrinkAnim(0.01);
		}
	}
	else
	{
		//
	}
}

void UOldPalFSM::TickDrinkCup()
{
	if(gi->checkDayCount == 1)
	{
		if(bCheckPlayAnim != true && curTime > 1 && drinkCount == 0)
		{
			bCheckPlayAnim = true;

			drinkCount++;

			// 올드팔 대사 10
			owner->oldPal_UI->SetOldPalText(11);
			owner->oldPal_UI->StartOldPal();
			
			// 살짝 마시는 애니메이션 실행
			owner->oldPalAnim->OnDrinkAnim(5.68);
		}
		else if(bCheckPlayAnim != true && curTime > 2 && drinkCount == 1)
		{
			bCheckPlayAnim = true;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			// 많이 마시는 애니메이션 실행
			owner->oldPalAnim->OnDrinkAnim(2.01);
		}
	}
	else
	{
		//
	}
		
}

void UOldPalFSM::TickUnHoldCup()
{
	if(gi->checkDayCount == 1)
	{
		if(bCheckPlayAnim != true && curTime > 1)
		{
			bCheckPlayAnim = true;

			// 컵 놓는 애니메이션 실행
			owner->oldPalAnim->OnDrinkAnim(7.67);
		}
	}
	else
	{
		//
	}
}