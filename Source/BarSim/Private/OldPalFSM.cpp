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
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
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

	owner->GetMesh()->SetRelativeLocation(FVector(0, 0, -3));

	owner->AttachToComponent(spawnManager->aChairs[idx]->sitComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// 손님 의자에 detach
void UOldPalFSM::DetachCustomer()
{
	owner->GetCapsuleComponent()->SetEnableGravity(true);
	
	owner->GetMesh()->SetRelativeLocation(FVector(0, 0, 5));
	
	owner->DetachAllSceneComponents(spawnManager->aChairs[idx]->sitComp, FDetachmentTransformRules::KeepWorldTransform);
}

// 주문 칵테일 정하기
void UOldPalFSM::SetOrderCoctail()
{
	if(gi->checkDayCount == 3)
	{
		// 올드팔
		orderIdx = 5;
	}
}

// -------------------------------------------------------------------------idle
// idle 상태 설정 함수
void UOldPalFSM::SetState(EOldPalState next)
{
	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;
	
	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;
	
	// 시간 초기화
	bCount = false;

	// 대화 초기화
	bPlayerTalk = false;

	bOldPalTalk = false;
	
	// 상태를 anim 클래스에 동기화
	owner->oldPalAnim->ownerState = next;
	
	state = next;
}

void UOldPalFSM::PlayOldPalVoice1(int32 index)
{
	UAudioComponent* oldPalVoice1 = Cast<UAudioComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("OldPalVoice1st")));

	if(oldPalVoice1)
	{
		oldPalVoice1->SetIntParameter("OldPalVoice1", index);
		oldPalVoice1->Play();
	}
}

void UOldPalFSM::PlayOldPalVoice3(int32 index1, int32 index2)
{
	UAudioComponent* oldPalVoice3 = Cast<UAudioComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("OldPalVoice3rd")));

	if(oldPalVoice3)
	{
		oldPalVoice3->SetIntParameter("Switch", index1);
		if(index1 == 0)
		{
			oldPalVoice3->SetIntParameter("OldPalVoice3", index2);
			oldPalVoice3->Play();
		}
		else
		{
			oldPalVoice3->SetIntParameter("OldPalVoice4", index2-30);
			oldPalVoice3->Play();
		}
	}
}

void UOldPalFSM::PlayPlayerVoice1(int32 index)
{
	UAudioComponent* playerVoice1 = Cast<UAudioComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("PlayerVoice1st")));

	if(playerVoice1)
	{
		playerVoice1->SetIntParameter("PlayerVoice1", index);
		playerVoice1->Play();
	}
}

void UOldPalFSM::PlayPlayerVoice3(int32 index)
{
	UAudioComponent* playerVoice3 = Cast<UAudioComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("PlayerVoice3rd")));

	if(playerVoice3)
	{
		playerVoice3->SetIntParameter("PlayerVoice3", index);
		playerVoice3->Play();
	}
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
			if(bPlayerTalk != true && curTime > 1)
			{
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(0);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice1(0);
				
				bPlayerTalk = true;
			}
			
			if(bCheckPlayAnim != true)
			{
				bCheckPlayAnim = true;
			
				// 도착하면 기대는 애니메이션 실행
				owner->oldPalAnim->OnStandAnim(2.01);
			}
		}
		// 3일
		else
		{
			if(bCheckPlayAnim != true)
			{
				bCheckPlayAnim = true;
			
				// 도착하면 기대는 애니메이션 실행
				owner->oldPalAnim->OnStandAnim(2.01);
			}
		}
	}
}

void UOldPalFSM::TickTalk()
{
	if(gi->checkDayCount == 1)
	{
		if(bPlayerTalk != true && curTime > 3)
		{
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();

			bPlayerTalk = true;

			if(bOldPalTalk != true)
			{
				owner->oldPal_UI->SetOldPalText(0);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(0);

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
	// 3일
	else
	{
		if(bOldPalTalk != true && curTime > 1 && curTime <= 4)
		{
			// 올드팔 대사 0
			owner->oldPal_UI->SetOldPalText(0);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,0);
			
			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				bCheckPlayAnim = true;
			
				// 말하는 애니메이션 실행
				owner->oldPalAnim->OnLeanAnim(4.51);
			}
		}

		if(bOldPalTalk != false && curTime > 4 && curTime <= 7)
		{
			// 올드팔 대사 1
			owner->oldPal_UI->SetOldPalText(1);

			PlayOldPalVoice3(0,1);

			bOldPalTalk = false;
		}

		if(bOldPalTalk != true && curTime > 7 && curTime <= 9)
		{
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = true;
		}

		if(bPlayerTalk != true && curTime > 9 && curTime <= 12)
		{
			// 플레이어 대사 0
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(0);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(0);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 12 && curTime <= 14)
		{
			// 플레이어 대사 1
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(1);

			PlayPlayerVoice3(1);

			bPlayerTalk = false;
		}

		if(bPlayerTalk != true && curTime > 14 && curTime <= 16)
		{
			player->playerText_UI->EndPlayer();

			bPlayerTalk = true;
		}

		if(bOldPalTalk != false && curTime > 16 && curTime <= 20)
		{
			// 올드팔 대사 2
			owner->oldPal_UI->SetOldPalText(2);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,2);

			bOldPalTalk = false;

			if(bCheckPlayAnim != false)
			{
				bCheckPlayAnim = false;
			
				// 말하는 애니메이션 실행
				owner->oldPalAnim->OnLeanAnim(4.51);
			}
		}

		if(bOldPalTalk != true && curTime > 20 && curTime <= 22)
		{
			// 올드팔 대사 3
			owner->oldPal_UI->SetOldPalText(3);

			PlayOldPalVoice3(0,3);

			bOldPalTalk = true;
		}

		if(bOldPalTalk != false && curTime > 22 && curTime <= 24)
		{
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = false;
		}

		if(bPlayerTalk != false && curTime > 24 && curTime <= 26)
		{
			// 플레이어 대사 2
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(2);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(2);

			bPlayerTalk = false;
		}

		if(bPlayerTalk != true && curTime > 26 && curTime <= 28)
		{
			// 플레이어 대사 3
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(3);

			PlayPlayerVoice3(3);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 28 && curTime <= 30)
		{
			player->playerText_UI->EndPlayer();

			bPlayerTalk = false;
		}

		if(bOldPalTalk != true && curTime > 29)
		{
			// 올드팔 대사 4
			owner->oldPal_UI->SetOldPalText(4);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,4);

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

void UOldPalFSM::TickChoice()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 3)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = true;
		}
		
		if(bCheckPlayAnim != true && curTime > 6)
		{
			owner->oldPal_UI->SetOldPalText(1);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(1);
			
			bCheckPlayAnim = true;
		
			// 말하는 애니메이션 실행
			owner->oldPalAnim->OnLeanAnim(4.51);
		}

		if(curTime > 10)
		{
			SetState(EOldPalState::READYMOVE);
		}
	}
	// 3일
	else
	{
		if(bOldPalTalk != true && curTime > 1 && curTime <= 3)
		{
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = true;
		}

		if(bPlayerTalk != true && curTime > 3 && curTime <= 6)
		{
			// 플레이어 대사 4
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(4);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(4);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 6 && curTime <= 9)
		{
			// 플레이어 대사 5
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(5);
			
			PlayPlayerVoice3(5);

			bPlayerTalk = false;
		}

		if(bPlayerTalk != true && curTime > 9 && curTime <= 12)
		{
			// 플레이어 대사 6
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(6);
			
			PlayPlayerVoice3(6);

			bPlayerTalk = true;
		}
		
		if(bPlayerTalk != false && curTime > 12 && curTime <= 14)
		{
			player->playerText_UI->EndPlayer();

			bPlayerTalk = false;
		}

		if(bOldPalTalk != false && curTime > 12 && curTime <= 14)
		{
			// 올드팔 대사 5
			owner->oldPal_UI->SetOldPalText(5);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,5);

			bOldPalTalk = false;

			if(bCheckPlayAnim != true)
			{
				bCheckPlayAnim = true;
			
				// 말하는 애니메이션 실행
				owner->oldPalAnim->OnLeanAnim(4.51);
			}
		}
		
		if(bOldPalTalk != true && curTime > 14 && curTime <= 18)
		{
			// 올드팔 대사 6
			owner->oldPal_UI->SetOldPalText(6);

			PlayOldPalVoice3(0,6);

			bOldPalTalk = true;
		}

		if(bOldPalTalk != false && curTime > 18 && curTime <= 20)
		{
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = false;
		}

		if(bPlayerTalk != true && curTime > 19 && curTime <= 22)
		{
			// 플레이어 대사 7
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(7);
			player->playerText_UI->StartPlayer();
			
			PlayPlayerVoice3(7);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 24)
		{
			player->playerText_UI->EndPlayer();

			bPlayerTalk = false;

			SetState(EOldPalState::READYMOVE);
		}
	}
}

void UOldPalFSM::TickReadyMove()
{
	if(gi->checkDayCount == 1)
	{
		// 의자의 저장하고
		idx = 0;
		
		// 앉은 의자 배열에 착석 여부 바꾸기
		spawnManager->aChairs[idx]->bCheck = true;

		// 선택지 띄우기
		if(player->playerText_UI->choiceCount == 0)
		{
			if(bPlayerTalk != true && curTime > 1)
			{
				// 플레이어 초이스 1번째
				player->playerText_UI->SetSwitcher(1);
				player->playerText_UI->SetChoice1();
				player->playerText_UI->StartPlayer();
				player->playerTextWidget->SetCollisionProfileName(TEXT("UI"));

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
				player->playerTextWidget->SetCollisionProfileName(TEXT("NoCollision"));
				
				bPlayerTalk = false;
			}
			
			if(curTime > 1 && bCheckPlayAnim != true)
			{
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(1);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice1(1);
				
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
				player->playerTextWidget->SetCollisionProfileName(TEXT("NoCollision"));

				bPlayerTalk = false;
			}

			if(curTime > 1 && bCheckPlayAnim != true)
			{
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(2);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice1(2);
				
				bCheckPlayAnim = true;
			
				// 다시 일어서는 애니메이션 실행
				owner->oldPalAnim->OnLeanAnim(0.01);
			}
		}
	}
	// 3일
	else
	{
		// 의자의 저장하고
		idx = 0;
		
		// 앉은 의자 배열에 착석 여부 바꾸기
		spawnManager->aChairs[idx]->bCheck = true;

		// 선택지 띄우기
		if(player->playerText_UI->choiceCount == 0)
		{
			if(bPlayerTalk != true && curTime > 2)
			{
				// 플레이어 초이스 2번째
				player->playerText_UI->SetSwitcher(1);
				player->playerText_UI->SetChoice2();
				player->playerText_UI->StartPlayer();
				player->playerTextWidget->SetCollisionProfileName(TEXT("UI"));

				bPlayerTalk = true;
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
				player->playerTextWidget->SetCollisionProfileName(TEXT("NoCollision"));
				
				bPlayerTalk = false;
			}
			
			if(curTime > 1 && bCheckPlayAnim != true)
			{
				// 플레이어 대사 8
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(8);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice3(8);

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
				player->playerTextWidget->SetCollisionProfileName(TEXT("NoCollision"));
				
				bPlayerTalk = false;
			}
			
			if(curTime > 1 && bCheckPlayAnim != true)
			{
				// 플레이어 대사 9
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(9);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice3(9);

				bCheckPlayAnim = true;
			
				// 다시 일어서는 애니메이션 실행
				owner->oldPalAnim->OnLeanAnim(0.01);
			}
		}
	}
}

void UOldPalFSM::TickMove()
{
	if(gi->checkDayCount == 1)
	{
		// 지정 된 의자 뒤로 이동
		auto loc = spawnManager->aChairs[idx]->GetActorLocation() + spawnManager->aChairs[idx]->GetActorForwardVector() * -100;

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
	// 3일
	else
	{
		// 지정 된 의자 뒤로 이동
		auto loc = spawnManager->aChairs[idx]->GetActorLocation() + spawnManager->aChairs[idx]->GetActorForwardVector() * -100;

		auto result = ai->MoveToLocation(loc);

		player->playerText_UI->choiceCount = 0;
		
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
}

void UOldPalFSM::TickReadySit()
{
	if(gi->checkDayCount == 1)
	{
		// 지정 된 의자 뒤로 이동
		auto loc = spawnManager->aChairs[idx]->GetActorLocation() + spawnManager->aChairs[idx]->GetActorForwardVector() * -10;
		auto result = ai->MoveToLocation(loc);

		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			if(bPlayerTalk != true)
			{
				// 플레이어 대사 3
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(3);
				player->playerText_UI->StartPlayer();

				//음성 X

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
	// 3일
	else
	{
		// 지정 된 의자 뒤로 이동
		auto loc = spawnManager->aChairs[idx]->GetActorLocation() + spawnManager->aChairs[idx]->GetActorForwardVector() * -10;
		auto result = ai->MoveToLocation(loc);

		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			if(bCheckPlayAnim != true)
			{
				// 도착하면 앉는 애니메이션 실행
				bCheckPlayAnim = true;

				owner->oldPalAnim->OnStandAnim(0.01);
			}
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
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(5);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice1(5);
			
			bPlayerTalk = true;
		}

		if(bOldPalTalk != true && curTime > 5)
		{
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(6);

			bOldPalTalk = true;
		}

		if(bCheckPlayAnim != true && curTime > 7)
		{
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(7);

			bCheckPlayAnim = true;
		}

		if(curTime > 9)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
		}
	}
	// 3일
	else
	{
		// 문 밖의 스폰매니저 주변으로 이동
		auto loc = spawnManager->GetActorLocation();

		auto result = ai->MoveToLocation(loc);

		if(result == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			owner->GetCharacterMovement()->MaxWalkSpeed = 0;
		}

		if(bPlayerTalk != true && curTime > 3 && curTime <= 6)
		{
			// 플레이어 대사 28
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(28);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(28);
			
			bPlayerTalk = true;
		}
		
		if(bPlayerTalk != false && curTime > 6 && curTime <= 8)
		{
			// 플레이어 대사 29
			player->playerText_UI->SetPlayerText(29);

			PlayPlayerVoice3(29);

			bPlayerTalk = false;
		}

		if(bPlayerTalk != true && curTime > 8 && curTime <= 10)
		{
			// 플레이어 대사 30
			player->playerText_UI->SetPlayerText(30);
			
			PlayPlayerVoice3(30);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 10 && curTime <= 12)
		{
			// 플레이어 대사 31
			player->playerText_UI->SetPlayerText(31);

			PlayPlayerVoice3(22);

			bPlayerTalk = false;
		}
		
		if(curTime > 14)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "BarStartMap");
		}
	}
}

// ---------------------------------------------------------------------------sit
// sit 상태 설정 함수
void UOldPalFSM::SetSitState(EOldPalSitState next)
{
	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;

	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;
	
	// 시간 초기화
	bCount = false;

	// 대화 초기화
	bPlayerTalk = false;

	bOldPalTalk = false;
	
	// 상태를 anim 클래스에 동기화
	owner->oldPalAnim->ownerSitState = next;
	
	sitState = next;
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
			owner->oldPal_UI->SetOldPalText(2);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(2);
			
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
	// 3일
	else
	{
		if(bOldPalTalk != true && curTime > 1 && curTime <= 5)
		{
			// 올드팔 대사 7
			owner->oldPal_UI->SetOldPalText(7);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,7);

			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크2 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(5.01);
			}
		}

		if(bOldPalTalk != false && curTime > 5 && curTime <= 7)
		{
			owner->oldPal_UI->EndOldPal();

			bOldPalTalk = false;
		}

		if(curTime > 5)
		{
			SetSitState(EOldPalSitState::ORDER);
		}
	}
}

void UOldPalFSM::TickStandbyWaitLong()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			owner->oldPal_UI->SetOldPalText(5);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(5);
			
			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크1 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(3.68);
			}
		}
		
		// 코스터가 있으면
		if(spawnManager->bIsCoaster[idx] != false && curTime > 3)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::ORDER);
		}
	}
	// 3일
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
			owner->oldPal_UI->SetOldPalText(3);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(3);
			
			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크0 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(0.01);
			}
		}

		if(curTime > 4)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::WAIT);
		}
	}
	// 3일
	else
	{
		if(bOldPalTalk != true && curTime > 1 && curTime <= 3)
		{
			// 올드팔 레시피 대사
			owner->oldPal_UI->SetOldPalRecipe();
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,8);

			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크0 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(0.01);
			}
		}

		if(curTime > 3)
		{
			SetSitState(EOldPalSitState::WAIT);
		}
	}
}

void UOldPalFSM::TickWait()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			owner->oldPal_UI->SetOldPalText(4);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(4);
			
			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크2 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(5.01);
			}
		}
		
		// 일정 시간안에 코스터와 칵테일이 준비 되면 상태 이동
		if(curTime > 5 && curTime <= 10 && spawnManager->bIsCoaster[idx] != false && spawnManager->bIsCoctail[idx] != false && player->isDropped == true)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();

			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(4);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice1(4);
			
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
	// 3일
	else
	{
		if(curTime > 1 && spawnManager->bIsCoaster[idx] != false && spawnManager->bIsCoctail[idx] != false && player->isDropped == true)
		{
			owner->oldPal_UI->EndOldPal();
			
			SetSitState(EOldPalSitState::ORDERJUDGE);
		}
	}
}

void UOldPalFSM::TickWaitLong()
{
	if(gi->checkDayCount == 1)
	{
		if(bOldPalTalk != true && curTime > 1)
		{
			owner->oldPal_UI->SetOldPalText(6);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(6);
			
			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크1 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(3.68);
			}
		}
		
		// 코스터와 칵테일이 준비 되면 상태 이동
		if(curTime > 2 && spawnManager->bIsCoaster[idx] != false && spawnManager->bIsCoctail[idx] != false && player->isDropped == true)
		{
			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
			
			if(bPlayerTalk != true)
			{
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(4);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice1(4);
				
				bPlayerTalk = true;
				
				SetSitState(EOldPalSitState::ORDERJUDGE);
			}
		}
	}
	// 3일
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
			if(bPlayerTalk != true && curTime > 2)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				owner->oldPal_UI->SetOldPalText(7);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(7);
				
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
		// 다이커리를 주면
		else if(spawnManager->orderCoctailIdx[idx] == 2)
		{
			if(bPlayerTalk != true && curTime > 2)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				owner->oldPal_UI->SetOldPalText(8);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(8);
				
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
		// 마티니를 주면
		else if(spawnManager->orderCoctailIdx[idx] == 3)
		{
			if(bPlayerTalk != true && curTime > 2)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				owner->oldPal_UI->SetOldPalText(9);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(9);
				
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
		// 네그로니를 주면
		else if(spawnManager->orderCoctailIdx[idx] == 4)
		{
			if(bPlayerTalk != true && curTime > 2)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				owner->oldPal_UI->SetOldPalText(10);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(10);
				
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
		// 그이외 모든것
		else if(spawnManager->orderCoctailIdx[idx] == 6)
		{
			if(bPlayerTalk != true && curTime > 2)
			{
				// 플레이어 대사 지우기
				player->playerText_UI->EndPlayer();

				bPlayerTalk = true;
			}

			if(bOldPalTalk != true && curTime > 3)
			{
				owner->oldPal_UI->SetOldPalText(11);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(11);
				
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
	// 3일
	else
	{
		if(bOldPalTalk != true && curTime > 1 && curTime <= 3)
		{
			// 올드팔 대사 11
			owner->oldPal_UI->text_oldpal1->SetText(FText::FromString(""));
			owner->oldPal_UI->text_oldpal2->SetText(FText::FromString(""));
			owner->oldPal_UI->SetOldPalText(11);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,11);
			
			bOldPalTalk = true;

			if(bCheckPlayAnim != true)
			{
				// 토크2 애니메이션 실행
				bCheckPlayAnim = true;
			
				owner->oldPalAnim->OnSitAnim(5.01);
			}
		}

		if(curTime > 3)
		{
			SetSitState(EOldPalSitState::HOLDCUP);

			spawnManager->aChairs[idx]->MoveCup();
		}
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
	// 3일
	else
	{
		if(bOldPalTalk != true && curTime > 1)
		{
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

				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(13);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(14);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(14);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 0 && spawnManager->scoreIdx[0] == 0 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(16);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(16);
				
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

				owner->oldPal_UI->SetOldPalText(15);
				owner->oldPal_UI->StartOldPal();
				
				PlayOldPalVoice1(15);
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[0] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(13);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(14);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(14);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[2] == 0 && spawnManager->scoreIdx[1] == 0 && spawnManager->scoreIdx[0] == 0 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(16);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(16);
				
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

				owner->oldPal_UI->SetOldPalText(15);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(15);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[0] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(13);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(14);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(14);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[2] == 0 && spawnManager->scoreIdx[1] == 0 && spawnManager->scoreIdx[0] == 0 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(16);
				owner->oldPal_UI->StartOldPal();
				
				PlayOldPalVoice1(16);
				
				// 토크2 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(5.01);

				SetSitState(EOldPalSitState::ANGRY);
			}
		}
		// 네그로니 이였다면
		if(spawnManager->orderCoctailIdx[idx] == 4)
		{
			if(spawnManager->scoreIdx[0] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(13);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 1 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(14);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(14);
				
				// 토크1 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(3.68);

				SetSitState(EOldPalSitState::ANGRY);
			}
			else if(spawnManager->scoreIdx[1] == 0 && spawnManager->scoreIdx[0] == 0 && bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(16);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(16);
				
				// 토크2 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(5.01);

				SetSitState(EOldPalSitState::ANGRY);
			}
		}
		else if(spawnManager->orderCoctailIdx[idx] == 6)
		{
			if(bOldPalTalk != true)
			{
				bOldPalTalk = true;

				owner->oldPal_UI->SetOldPalText(17);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice1(17);
				
				// 토크2 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(5.01);

				SetSitState(EOldPalSitState::ANGRY);
			}
		}
	}
	// 3일
	else
	{
		if(spawnManager->aChairs[idx]->bSameOrder == true)
		{
			if(spawnManager->orderScore >= 50)
			{
				if(bOldPalTalk != true && curTime > 1 && curTime <= 5)
				{
					bOldPalTalk = true;

					// 올드팔 대사 14
					owner->oldPal_UI->SetOldPalText(14);
					owner->oldPal_UI->StartOldPal();

					PlayOldPalVoice3(0,14);

					// 좋아하는 애니메이션 실행
					owner->oldPalAnim->OnSitAnim(7.34);
				}

				if(bOldPalTalk != false && curTime > 5 && curTime <= 7)
				{
					bOldPalTalk = false;

					// 올드팔 대사 지우기
					owner->oldPal_UI->EndOldPal();
				}
				
				if(bPlayerTalk != true && curTime > 6 && curTime <= 8)
				{
					bPlayerTalk = true;

					// 플레이어 대사 10
					player->playerText_UI->SetSwitcher(0);
					player->playerText_UI->SetPlayerText(10);
					player->playerText_UI->StartPlayer();
				}

				if(bPlayerTalk != false && curTime > 8 && curTime <= 10)
				{
					bPlayerTalk = false;
					
					// 플레이어 대사 지우기
					player->playerText_UI->EndPlayer();
				}
				
				if(bOldPalTalk != true && curTime > 9 && curTime <= 12)
				{
					bOldPalTalk = true;

					// 올드팔 대사 15
					owner->oldPal_UI->SetOldPalText(15);
					owner->oldPal_UI->StartOldPal();

					PlayOldPalVoice3(0,15);
					
					// 토크0 애니메이션 실행
					owner->oldPalAnim->OnSitAnim(0.01);
				}
				
				if(curTime > 12)
				{
					SetSitState(EOldPalSitState::ANGRY);
				}
			}
			else
			{
				if(bOldPalTalk != true && curTime > 1 && curTime <= 4)
				{
					bOldPalTalk = true;

					// 올드팔 대사 12
					owner->oldPal_UI->SetOldPalText(12);
					owner->oldPal_UI->StartOldPal();

					PlayOldPalVoice3(0,12);

					// 토크1 애니메이션 실행
					owner->oldPalAnim->OnSitAnim(3.68);
				}

				if(bOldPalTalk != false && curTime > 4 && curTime <= 6)
				{
					bOldPalTalk = false;

					owner->oldPal_UI->EndOldPal();

					spawnManager->aChairs[idx]->ViewInfo();
				}
			
				if(spawnManager->bIsCoaster[idx] != true && spawnManager->bIsCoctail[idx] != true)
				{
					spawnManager->aChairs[idx]->HideScore();
				
					spawnManager->aChairs[idx]->bOnceOverlap = false;

					SetSitState(EOldPalSitState::ORDER);

					drinkState = EOldPalDrinkState::IDLE;
					
					spawnManager->aChairs[idx]->bSameOrder = false;
				}
			}
		}
		else if(spawnManager->aChairs[idx]->bUnSameOrder == true)
		{
			if(bOldPalTalk != true && curTime > 1 && curTime <= 4)
			{
				bOldPalTalk = true;

				// 올드팔 대사 13
				owner->oldPal_UI->SetOldPalText(13);
				owner->oldPal_UI->StartOldPal();

				PlayOldPalVoice3(0,13);

				// 화내는 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(9.24);
			}

			if(bOldPalTalk != false && curTime > 4 && curTime <= 6)
			{
				bOldPalTalk = false;

				owner->oldPal_UI->EndOldPal();

				spawnManager->aChairs[idx]->ViewInfo();
			}
			
			if(spawnManager->bIsCoaster[idx] != true && spawnManager->bIsCoctail[idx] != true)
			{
				spawnManager->aChairs[idx]->HideScore();
				
				spawnManager->aChairs[idx]->bOnceOverlap = false;

				SetSitState(EOldPalSitState::ORDER);
				
				drinkState = EOldPalDrinkState::IDLE;
				
				spawnManager->aChairs[idx]->bUnSameOrder = false;
			}
		}
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
			owner->oldPal_UI->SetOldPalText(18);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(18);
			
			bCheckPlayAnim = true;

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);

			SetSitState(EOldPalSitState::AWESOME);
		}
	}
	// 3일
	else
	{
		if(bOldPalTalk != true && curTime > 1 && curTime <= 3)
		{
			bOldPalTalk = true;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != true && curTime > 3 && curTime <= 7)
		{
			bPlayerTalk = true;

			// 플레이어 대사 11
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(11);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(11);
		}

		if(bPlayerTalk != false && curTime > 7 && curTime <= 9)
		{
			bPlayerTalk = false;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != false && curTime > 8 && curTime <= 10)
		{
			bOldPalTalk = false;

			// 올드팔 대사 16
			owner->oldPal_UI->SetOldPalText(16);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,16);

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != true && curTime > 10 && curTime <= 14)
		{
			// 올드팔 대사 17
			owner->oldPal_UI->SetOldPalText(17);

			PlayOldPalVoice3(0,17);

			bOldPalTalk = true;
		}

		if(bOldPalTalk != false && curTime > 14 && curTime <= 16)
		{
			bOldPalTalk = false;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bOldPalTalk != true && curTime > 16 && curTime <= 21)
		{
			bOldPalTalk = true;

			// 올드팔 대사 18
			owner->oldPal_UI->SetOldPalText(18);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,18);

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != false && curTime > 21 && curTime <= 24)
		{
			// 올드팔 대사 19
			owner->oldPal_UI->SetOldPalText(19);
			
			PlayOldPalVoice3(0,19);

			bOldPalTalk = false;
		}

		if(bOldPalTalk != true && curTime > 24 && curTime <= 26)
		{
			bOldPalTalk = true;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}
		
		if(bPlayerTalk != true && curTime > 25 && curTime <= 27)
		{
			bPlayerTalk = true;

			// 플레이어 대사 12
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(12);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(12);
		}

		if(bPlayerTalk != false && curTime > 27 && curTime <= 29)
		{
			bPlayerTalk = false;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != false && curTime > 28 && curTime <= 31)
		{
			bOldPalTalk = false;

			// 올드팔 대사 20
			owner->oldPal_UI->SetOldPalText(20);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,20);

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != true && curTime > 31 && curTime <= 33)
		{
			bOldPalTalk = true;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != true && curTime > 32 && curTime <= 36)
		{
			bPlayerTalk = true;

			// 플레이어 대사 13
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(13);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(13);
		}

		if(bPlayerTalk != false && curTime > 36 && curTime <= 38)
		{
			bPlayerTalk = false;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != false && curTime > 37 && curTime <= 40)
		{
			bOldPalTalk = false;

			// 올드팔 대사 21
			owner->oldPal_UI->SetOldPalText(21);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,21);

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != true && curTime > 40 && curTime <= 45)
		{
			// 올드팔 대사 22
			owner->oldPal_UI->SetOldPalText(22);

			PlayOldPalVoice3(0,22);
			
			bOldPalTalk = true;
		}

		if(bCheckPlayAnim != true && curTime > 45 && curTime <= 48)
		{
			// 올드팔 대사 23
			owner->oldPal_UI->SetOldPalText(23);

			PlayOldPalVoice3(0,23);

			bCheckPlayAnim = true;

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != false && curTime > 48 && curTime <= 50)
		{
			bOldPalTalk = false;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != true && curTime > 49 && curTime <= 52)
		{
			bPlayerTalk = true;

			// 플레이어 대사 14
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(14);
			player->playerText_UI->StartPlayer();
			
			PlayPlayerVoice3(14);
		}

		if(bPlayerTalk != false && curTime > 52 && curTime <= 57)
		{
			// 플레이어 대사 15
			player->playerText_UI->SetPlayerText(15);

			PlayPlayerVoice3(15);

			bPlayerTalk = false;
		}

		if(bPlayerTalk != true && curTime > 57 && curTime <= 60)
		{
			// 플레이어 대사 16
			player->playerText_UI->SetPlayerText(16);

			PlayPlayerVoice3(16);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 60 && curTime <= 63)
		{
			// 플레이어 대사 17
			player->playerText_UI->SetPlayerText(17);

			PlayPlayerVoice3(17);

			bPlayerTalk = false;
		}

		if(bPlayerTalk != true && curTime > 63 && curTime <= 65)
		{
			bPlayerTalk = true;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != true && curTime > 64 && curTime <= 68)
		{
			bOldPalTalk = true;

			// 올드팔 대사 24
			owner->oldPal_UI->SetOldPalText(24);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,24);

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != false && curTime > 68 && curTime <= 70)
		{
			bOldPalTalk = false;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != false && curTime > 69 && curTime <= 71)
		{
			bPlayerTalk = false;

			// 플레이어 대사 18
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(18);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(18);
		}

		if(bPlayerTalk != true && curTime > 71 && curTime <= 73)
		{
			bPlayerTalk = true;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != true && curTime > 72 && curTime <= 77)
		{
			bOldPalTalk = true;

			// 올드팔 대사 25
			owner->oldPal_UI->SetOldPalText(25);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,25);

			// 토크1 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(3.68);
		}

		if(bCheckPlayAnim != false && curTime > 77 && curTime <= 80)
		{
			// 올드팔 대사 26
			owner->oldPal_UI->SetOldPalText(26);

			PlayOldPalVoice3(0,26);
			
			bCheckPlayAnim = false;

			// 좋아하는 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(7.34);
		}

		if(bOldPalTalk != false && curTime > 80 && curTime <= 82)
		{
			bOldPalTalk = false;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != false && curTime > 81 && curTime <= 83)
		{
			bPlayerTalk = false;

			// 플레이어 대사 19
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(19);
			player->playerText_UI->StartPlayer();
			
			PlayPlayerVoice3(19);
		}

		if(bPlayerTalk != true && curTime > 83 && curTime <= 85)
		{
			bPlayerTalk = true;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != true && curTime > 84 && curTime <= 87)
		{
			bOldPalTalk = true;

			// 올드팔 대사 27
			owner->oldPal_UI->SetOldPalText(27);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(0,27);

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != false && curTime > 87 && curTime <= 91)
		{
			// 올드팔 대사 28
			owner->oldPal_UI->SetOldPalText(28);

			PlayOldPalVoice3(0,28);

			bOldPalTalk = false;
		}

		if(bCheckPlayAnim != true && curTime > 91 && curTime <= 96)
		{
			// 올드팔 대사 29
			owner->oldPal_UI->SetOldPalText(29);

			PlayOldPalVoice3(0,29);

			bCheckPlayAnim = true;

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != true && curTime > 96 && curTime <= 98)
		{
			// 올드팔 대사 30
			owner->oldPal_UI->SetOldPalText(30);

			PlayOldPalVoice3(0,30);

			bOldPalTalk = true;
		}

		if(bOldPalTalk != false && curTime > 98 && curTime <= 100)
		{
			bOldPalTalk = false;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != false && curTime > 99 && curTime <= 102)
		{
			bPlayerTalk = false;

			// 플레이어 대사 20
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(20);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(20);
		}
		
		if(bPlayerTalk != true && curTime > 102 && curTime <= 105)
		{
			// 플레이어 대사 21
			player->playerText_UI->SetPlayerText(21);

			PlayPlayerVoice3(21);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 105 && curTime <= 107)
		{
			bPlayerTalk = false;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != true && curTime > 105 && curTime <= 109)
		{
			bOldPalTalk = true;

			// 올드팔 대사 31
			owner->oldPal_UI->SetOldPalText(31);
			owner->oldPal_UI->StartOldPal();
			
			PlayOldPalVoice3(1,31);

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != false && curTime > 109 && curTime <= 115)
		{
			// 올드팔 대사 32
			owner->oldPal_UI->SetOldPalText(32);
			
			PlayOldPalVoice3(1,32);
			
			bOldPalTalk = false;
		}

		if(bCheckPlayAnim != false && curTime > 115 && curTime <= 120)
		{
			// 올드팔 대사 33
			owner->oldPal_UI->SetOldPalText(33);

			PlayOldPalVoice3(1,33);

			bCheckPlayAnim = false;

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != true && curTime > 120 && curTime <= 123)
		{
			// 올드팔 대사 34
			owner->oldPal_UI->SetOldPalText(34);

			PlayOldPalVoice3(1,34);

			bOldPalTalk = true;
		}

		if(bCheckPlayAnim != true && curTime > 123 && curTime <= 126)
		{
			// 올드팔 대사 35
			owner->oldPal_UI->SetOldPalText(35);
			
			PlayOldPalVoice3(1,35);

			bCheckPlayAnim = true;

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}
		
		if(bOldPalTalk != false && curTime > 126 && curTime <= 130)
		{
			// 올드팔 대사 36
			owner->oldPal_UI->SetOldPalText(36);

			PlayOldPalVoice3(1,36);

			bOldPalTalk = false;
		}

		if(bOldPalTalk != true && curTime > 130 && curTime <= 132)
		{
			bOldPalTalk = true;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != true && curTime > 131 && curTime <= 135)
		{
			bPlayerTalk = true;

			// 플레이어 대사 22
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(22);
			player->playerText_UI->StartPlayer();
		}

		if(bPlayerTalk != false && curTime > 135)
		{
			bPlayerTalk = false;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();

			SetSitState(EOldPalSitState::AWESOME);
		}
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
			owner->oldPal_UI->SetOldPalText(19);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(19);
			
			bCheckPlayAnim = true;

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);

			SetSitState(EOldPalSitState::READYLEAVE);
		}
	}
	// 3일
	else
	{
		// 선택지 띄우기
		if(player->playerText_UI->choiceCount == 0)
		{
			if(bPlayerTalk != true && curTime > 1)
			{
				// 플레이어 초이스 3번째
				player->playerText_UI->SetSwitcher(1);
				player->playerText_UI->SetChoice3();
				player->playerText_UI->StartPlayer();
				player->playerTextWidget->SetCollisionProfileName(TEXT("UI"));

				bPlayerTalk = true;
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

			if(bPlayerTalk != false && curTime > 1 && curTime <= 3)
			{
				// 플레이어 초이스 지우기
				player->playerText_UI->EndPlayer();
				player->playerTextWidget->SetCollisionProfileName(TEXT("NoCollision"));
				
				bPlayerTalk = false;
			}

			if(bPlayerTalk != true && curTime > 3)
			{
				bPlayerTalk = true;

				// 플레이어 대사 23
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(23);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice3(23);

				SetSitState(EOldPalSitState::READYLEAVE);
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

			if(bPlayerTalk != false && curTime > 1 && curTime <= 3)
			{
				// 플레이어 초이스 지우기
				player->playerText_UI->EndPlayer();
				player->playerTextWidget->SetCollisionProfileName(TEXT("NoCollision"));
				
				bPlayerTalk = false;
			}

			if(bPlayerTalk != true && curTime > 3)
			{
				bPlayerTalk = true;

				// 플레이어 대사 24
				player->playerText_UI->SetSwitcher(0);
				player->playerText_UI->SetPlayerText(24);
				player->playerText_UI->StartPlayer();

				PlayPlayerVoice3(24);

				SetSitState(EOldPalSitState::READYLEAVE);
			}
		}
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

			float money = 5 + spawnManager->aChairs[idx]->totalScore/10;
		
			spawnManager->gi->AddMoney(money);

			UGameplayStatics::PlaySound2D(GetWorld(), owner->cashSound);

			if(bCheckPlayAnim != true)
			{
				bCheckPlayAnim = true;

				// 자리에서 일어나는 애니메이션 실행
				owner->oldPalAnim->OnSitAnim(10.70);

				owner->GetMesh()->SetRelativeLocation(FVector(-35, 0, -3));
			}
		}
	}
	// 3일
	else
	{
		if(bPlayerTalk != true && curTime > 1 && curTime <= 3)
		{
			bPlayerTalk = true;
			
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != true && curTime > 1 && curTime <= 3)
		{
			bOldPalTalk = true;

			// 올드팔 대사 37
			owner->oldPal_UI->SetOldPalText(37);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(1,37);

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != false && curTime > 3 && curTime <= 7)
		{
			// 올드팔 대사 38
			owner->oldPal_UI->SetOldPalText(38);

			PlayOldPalVoice3(1,38);

			bOldPalTalk = false;
		}

		if(bCheckPlayAnim != true && curTime > 7 && curTime <= 10)
		{
			// 올드팔 대사 39
			owner->oldPal_UI->SetOldPalText(39);
			
			PlayOldPalVoice3(1,39);

			bCheckPlayAnim = true;

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != true && curTime > 10 && curTime <= 15)
		{
			// 올드팔 대사 40
			owner->oldPal_UI->SetOldPalText(40);

			PlayOldPalVoice3(1,40);

			bOldPalTalk = true;
		}

		if(bCheckPlayAnim != false && curTime > 15 && curTime <= 22)
		{
			// 올드팔 대사 41
			owner->oldPal_UI->SetOldPalText(41);

			PlayOldPalVoice3(1,41);

			bCheckPlayAnim = false;

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != false && curTime > 22 && curTime <= 25)
		{
			// 올드팔 대사 42
			owner->oldPal_UI->SetOldPalText(42);

			PlayOldPalVoice3(1,42);

			bOldPalTalk = false;
		}
		
		if(bOldPalTalk != true && curTime > 25 && curTime <= 27)
		{
			bOldPalTalk = true;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}

		if(bPlayerTalk != false && curTime > 25 && curTime <= 28)
		{
			bPlayerTalk = false;

			// 플레이어 대사 25
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(25);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(25);
		}

		if(bPlayerTalk != true && curTime > 28 && curTime <= 31)
		{
			// 플레이어 대사 26
			player->playerText_UI->SetPlayerText(26);

			PlayPlayerVoice3(26);

			bPlayerTalk = true;
		}

		if(bPlayerTalk != false && curTime > 31 && curTime <= 33)
		{
			bPlayerTalk = false;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != false && curTime > 32 && curTime <= 35)
		{
			bOldPalTalk = false;

			// 올드팔 대사 43
			owner->oldPal_UI->SetOldPalText(43);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(1,43);

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != true && curTime > 35 && curTime <= 37)
		{
			// 올드팔 대사 44
			owner->oldPal_UI->SetOldPalText(44);

			PlayOldPalVoice3(1,44);

			bOldPalTalk = true;
		}
		
		if(bCheckPlayAnim != true && curTime > 37 && curTime <= 42)
		{
			// 올드팔 대사 45
			owner->oldPal_UI->SetOldPalText(45);

			PlayOldPalVoice3(1,45);

			bCheckPlayAnim = true;

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != false && curTime > 42 && curTime <= 44)
		{
			bOldPalTalk = false;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();
		}
		
		if(bPlayerTalk != true && curTime > 42 && curTime <= 44)
		{
			bPlayerTalk = true;

			// 플레이어 대사 27
			player->playerText_UI->SetSwitcher(0);
			player->playerText_UI->SetPlayerText(27);
			player->playerText_UI->StartPlayer();

			PlayPlayerVoice3(27);
		}
		
		if(bPlayerTalk != false && curTime > 44 && curTime <= 46)
		{
			bPlayerTalk = false;
					
			// 플레이어 대사 지우기
			player->playerText_UI->EndPlayer();
		}

		if(bOldPalTalk != true && curTime > 44 && curTime <= 47)
		{
			bOldPalTalk = true;

			// 올드팔 대사 46
			owner->oldPal_UI->SetOldPalText(46);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice3(1,46);

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != false && curTime > 47 && curTime <= 50)
		{
			// 올드팔 대사 47
			owner->oldPal_UI->SetOldPalText(47);

			PlayOldPalVoice3(1,47);

			bOldPalTalk = false;
		}

		if(bCheckPlayAnim != false && curTime > 50 && curTime <= 52)
		{
			// 올드팔 대사 48
			owner->oldPal_UI->SetOldPalText(48);

			PlayOldPalVoice3(1,48);

			bCheckPlayAnim = false;

			// 토크2 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(5.01);
		}

		if(bOldPalTalk != true && curTime > 52 && curTime <= 57)
		{
			// 올드팔 대사 49
			owner->oldPal_UI->SetOldPalText(49);
			
			PlayOldPalVoice3(1,49);

			bOldPalTalk = true;
		}

		if(bCheckPlayAnim != true && curTime > 57 && curTime <= 60)
		{
			// 올드팔 대사 50
			owner->oldPal_UI->SetOldPalText(50);

			PlayOldPalVoice3(1,50);

			bCheckPlayAnim = true;

			// 좋아하는 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(7.34);
		}

		if(bOldPalTalk != false && curTime > 60 && curTime <= 63)
		{
			// 올드팔 대사 51
			owner->oldPal_UI->SetOldPalText(51);

			PlayOldPalVoice3(1,51);

			bOldPalTalk = false;
		}

		if(bCheckPlayAnim != false && curTime > 63 && curTime <= 66)
		{
			// 올드팔 대사 52
			owner->oldPal_UI->SetOldPalText(52);

			PlayOldPalVoice3(1,52);

			bCheckPlayAnim = false;

			// 토크0 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(0.01);
		}

		if(bOldPalTalk != true && curTime > 66 && curTime <= 69)
		{
			// 올드팔 대사 53
			owner->oldPal_UI->SetOldPalText(53);

			PlayOldPalVoice3(1,53);
			
			bOldPalTalk = true;
		}

		if(bOldPalTalk != false && curTime > 69 && curTime <= 71)
		{
			bOldPalTalk = false;

			// 올드팔 대사 지우기
			owner->oldPal_UI->EndOldPal();

			float money = 5 + spawnManager->aChairs[idx]->totalScore/10;
		
			spawnManager->gi->AddMoney(money);

			UGameplayStatics::PlaySound2D(GetWorld(), owner->cashSound);
		}
		
		if(bCheckPlayAnim != true && curTime > 71)
		{
			bCheckPlayAnim = true;

			// 자리에서 일어나는 애니메이션 실행
			owner->oldPalAnim->OnSitAnim(10.70);

			owner->GetMesh()->SetRelativeLocation(FVector(-35, 0, -3));
		}
	}
}

// ---------------------------------------------------------------------------drink
// drink 상태 설정 함수
void UOldPalFSM::SetDrinkState(EOldPalDrinkState next)
{
	// 상태가 변경 될 때마다 대기시간 초기화
	curTime = 0;

	// 플레이 되는 애니메이션 플레이 체크 초기화
	bCheckPlayAnim = false;

	// 시간 초기화
	bCount = false;

	// 대화 초기화
	bPlayerTalk = false;

	bOldPalTalk = false;
	
	drinkState = next;
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
	// 3일
	else
	{
		if(bCheckPlayAnim != true && curTime > 1)
		{
			bCheckPlayAnim = true;

			// 잔을 들고 cheers 애니메이션 실행
			owner->oldPalAnim->OnDrinkAnim(0.01);
		}
	}
}

void UOldPalFSM::TickDrinkCup()
{
	if(gi->checkDayCount == 1)
	{
		if(bCheckPlayAnim != true && curTime > 3 && drinkCount == 0)
		{
			bCheckPlayAnim = true;

			drinkCount++;

			owner->oldPal_UI->SetOldPalText(12);
			owner->oldPal_UI->StartOldPal();

			PlayOldPalVoice1(12);
			
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
	// 3일
	else
	{
		if(spawnManager->aChairs[idx]->bSameOrder == true)
		{
			if(spawnManager->orderScore >= 60)
			{
				if(bCheckPlayAnim != true && curTime > 1 && drinkCount == 0)
				{
					bCheckPlayAnim = true;

					drinkCount++;
					
					// 살짝 마시는 애니메이션 실행
					owner->oldPalAnim->OnDrinkAnim(5.68);
				}
				else if(bCheckPlayAnim != true && curTime > 2 && drinkCount == 1)
				{
					bCheckPlayAnim = true;

					// 많이 마시는 애니메이션 실행
					owner->oldPalAnim->OnDrinkAnim(2.01);
				}
			}
			else
			{
				if(bCheckPlayAnim != true && curTime > 1)
				{
					bCheckPlayAnim = true;
				
					// 살짝 마시는 애니메이션 실행
					owner->oldPalAnim->OnDrinkAnim(5.68);
				}
			}
		}
		else if(spawnManager->aChairs[idx]->bUnSameOrder == true)
		{
			if(bCheckPlayAnim != true && curTime > 1)
			{
				bCheckPlayAnim = true;
				
				// 살짝 마시는 애니메이션 실행
				owner->oldPalAnim->OnDrinkAnim(5.68);
			}
		}
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
	// 3일
	else
	{
		if(bCheckPlayAnim != true && curTime > 1)
		{
			bCheckPlayAnim = true;

			// 컵 놓는 애니메이션 실행
			owner->oldPalAnim->OnDrinkAnim(7.67);
		}
	}
}