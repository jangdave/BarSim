// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "BarGameInstance.h"
#include "Chair.h"
#include "CustomerCharacter.h"
#include "EngineUtils.h"
#include "OldPalCharacter.h"
#include "PlayerCharacter.h"
#include "PlayerDialogWidget.h"
#include "Tablet.h"
#include "TabletWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	// 맵 상의 모든 의자 확인
	CheckChairSit();
	
	gi = Cast<UBarGameInstance>(GetGameInstance());
	
	tablet = Cast<ATablet>(UGameplayStatics::GetActorOfClass(GetWorld(), ATablet::StaticClass()));

	// 일정 시간마다 배열 초기화
	FTimerHandle check;
	GetWorldTimerManager().SetTimer(check, this, &ASpawnManager::CheckArray, 0.1, true);
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnManager::CheckChairSit()
{
	for(TActorIterator<AChair> chairs(GetWorld()); chairs; ++chairs)
	{
		auto chair = *chairs;

		if(chair != nullptr && chair->GetActorNameOrLabel() == "BP_Chair1")
		{
			aChairs[0] = chair;
		}
		else if(chair != nullptr && chair->GetActorNameOrLabel() == "BP_Chair2")
		{
			aChairs[1] = chair;
		}
		else if(chair != nullptr && chair->GetActorNameOrLabel() == "BP_Chair3")
		{
			aChairs[2] = chair;
		}
		else if(chair != nullptr && chair->GetActorNameOrLabel() == "BP_Chair4")
		{
			aChairs[3] = chair;
		}
	}
}

void ASpawnManager::CheckArray()
{
	// 배열을 초기화 하고
	bIsCoctail.Empty();
	bIsPlayer.Empty();
	bIsCoaster.Empty();

	// 모든 의자들을 확인해서 인자들 다시 채우기
	for(int i = 0; i<aChairs.Num(); i++)
	{
		bIsCoctail.Add(aChairs[i]->bCheckCoctail);
		bIsCoaster.Add(aChairs[i]->bCheckCoaster);
		bIsPlayer.Add(aChairs[i]->bCheckPlayer);
	}

	for(int i = 0; i<aChairs.Num(); i++)
	{
		if(aChairs[i]->bCheck != false)
		{
			return;
		}
	}

	if(tablet != nullptr && bCheckSpawn != false)
	{
		tablet->tablet_UI->btn_CloseStore->SetIsEnabled(true);
	}
}

void ASpawnManager::SpawnCustomer()
{
	SpawnCustom();
	
	// 시간이 지날때마다 손님을 스폰한다
	FTimerHandle spawnTime;
	GetWorldTimerManager().SetTimer(spawnTime, this, &ASpawnManager::SpawnCustom, 30, true);
}

void ASpawnManager::SpawnCustom()
{
	// 날짜가 지난만큼 더 많이 스폰
	int32 idx = (gi->checkDayCount - 1) * 4; // 4
	
	// 전체 손님 수가 지정한 숫자보다 작을때
	if(checkCustomerNum >= idx)
	{
		// 가게 오픈했는지 체크
		bCheckSpawn = true;
	}
	else if(checkCustomerNum < idx)
	{
		for(int i = 0; i<aChairs.Num(); i++)
		{
			// 빈자리가 있으면
			if(aChairs[i]->bCheck != true)
			{
				bCheckSit = true;
			}
		}
		// 손님을 스폰하고
		if(bCheckSit != false)
		{
			GetWorld()->SpawnActor<ACustomerCharacter>(customerFactory, GetActorLocation(), GetActorRotation());

			// 한명씩 카운트하기
			checkCustomerNum++;

			// 빈자리 채움
			bCheckSit = false;
		}
	}
}

void ASpawnManager::GetCustomerIdx(int32 orderIdx, int32 idx)
{
	orderCoctailIdx[idx] = orderIdx;
}

void ASpawnManager::SpawnOldPal()
{
	if(gi != nullptr)
	{
		if(gi->checkDayCount == 1 && bSpawnOld != true)
		{
			GetWorld()->SpawnActor<AOldPalCharacter>(oldPalFactory, GetActorLocation(), GetActorRotation());

			bSpawnOld = true;
		}
		else if(gi->checkDayCount == 2)
		{
			player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			
			FTimerHandle timer;
			GetWorldTimerManager().SetTimer(timer, this, &ASpawnManager::SecondDay, 0.1, true);
		}
		else if(gi->checkDayCount == 3 && bSpawnOld != true)
		{
			GetWorld()->SpawnActor<AOldPalCharacter>(oldPalFactory, GetActorLocation(), GetActorRotation());

			bSpawnOld = true;
		}
	}
}

void ASpawnManager::SecondDay()
{
	twoTimer += 0.1;

	if(twoTimer > 1 && bCheckTwo != true)
	{
		player->playerText_UI->SetSwitcher(0);
		player->playerText_UI->SetPlayerText(0);
		player->playerText_UI->StartPlayer();

		bCheckTwo = true;
	}

	if(twoTimer >= 4 && twoTimer < 7)
	{
		player->playerText_UI->SetPlayerText(1);
	}

	if(twoTimer >= 7 && twoTimer < 10)
	{
		player->playerText_UI->SetPlayerText(2);
	}

	if(twoTimer >= 10)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "StartMap");
	}
}

// 점수 체크------------------------------------------------------------------------------------------------------------
void ASpawnManager::GetCup(TArray<FString> cocName, TArray<float> cocliter, bool bStirred, bool bStirredLater, bool bShake, TArray<bool> garnishArray,  int32 customerIdx)
{
	amountOfWhiskey = 0;
	amountOfRum = 0;
	amountOfGin = 0;
	amountOfVermouth = 0;
	amountOfLime = 0;
	amountOfSugar = 0;
	amountOfCampari = 0;
	
	orderScore = 100;
	
	for(int i = 0; i<cocName.Num(); i++)
	{
		if(cocName[i] == "Whiskey")
		{
			amountOfWhiskey += cocliter[i];
		}
		else if(cocName[i] == "Rum")
		{
			amountOfRum += cocliter[i];
		}
		else if(cocName[i] == "Gin")
		{
			amountOfGin += cocliter[i];
		}
		else if(cocName[i] == "Vermouth")
		{
			amountOfVermouth += cocliter[i];
		}
		else if(cocName[i] == "Lime")
		{
			amountOfLime += cocliter[i];
		}
		else if(cocName[i] == "Campari")
		{
			amountOfCampari += cocliter[i];
		}
		else if(cocName[i] == "Sugar")
		{
			amountOfSugar += cocliter[i];
		}
	}
	
	if(amountOfGin > 0)
	{
		CheckGin(cocName, bStirred, bStirredLater, garnishArray, customerIdx);
	}
	else if(amountOfRum > 0)
	{
		CheckRum(cocName, bStirred, bStirredLater, bShake, garnishArray, customerIdx);
	}
	else if(amountOfWhiskey > 0)
	{
		CheckWhisky(cocName, bStirred, bStirredLater, customerIdx);
	}
	else
	{
		SomethingElse(customerIdx);
	}
}

void ASpawnManager::CheckGin(TArray<FString> cocName, bool bStirred, bool bStirredLater, TArray<bool> garnishArray, int32 customerIdx)
{
	// 진라임 판정
	if(amountOfLime > 0 && amountOfVermouth <= 0 && amountOfCampari <= 0)
	{
		if(cocName.Num() == GinLime.Num())
		{
			if(garnishArray[0] == true)
			{
				orderScore -= 0;
			}
			else
			{
				orderScore -= 10;
			}
			
			CheckGinLime(customerIdx);
		}
	}
	// 마티니 판정
	else if(amountOfVermouth > 0 && amountOfLime <= 0 && amountOfCampari <= 0)
	{
		if(cocName.Num() == Martini.Num())
		{
			if(bStirred != false && bStirredLater != true)
			{
				orderScore -= 0;
			}
			else if(bStirred != false && bStirredLater != false)
			{
				orderScore -= 10;
			}
			else
			{
				orderScore -= 25;

				scoreIdx[2] = 1;
			}

			if(garnishArray[1] == true)
			{
				orderScore -= 0;
			}
			else
			{
				orderScore -= 15;
			}
			
			CheckMartini(customerIdx);
		}
	}
	// 네그로니 판정
	else if(amountOfCampari > 0 && amountOfVermouth > 0 && amountOfLime <= 0)
	{
		if(cocName.Num() == Negroni.Num())
		{
			if(garnishArray[2] == true)
			{
				orderScore -= 0;
			}
			else
			{
				orderScore -= 20;
			}
			
			CheckNegroni(customerIdx);
		}
	}
	// 레시피 범위 밖
	else
	{
		SomethingElse(customerIdx);
	}
	
}

void ASpawnManager::CheckWhisky(TArray<FString> cocName, bool bStirred, bool bStirredLater, int32 customerIdx)
{
	// 올드팔 판정
	if(amountOfVermouth > 0 && amountOfCampari > 0 && amountOfLime <= 0)
	{
		if(cocName.Num() == OldPal.Num())
		{
			if(bStirred != false && bStirredLater != true)
			{
				orderScore -= 0;
			}
			else if(bStirred != false && bStirredLater != false)
			{
				orderScore -= 10;
			}
			else
			{
				orderScore -= 30;
			}
			
			CheckOldPal(customerIdx);
		}		
	}
	// 레시피 범위 밖
	else
	{
		SomethingElse(customerIdx);
	}
}

void ASpawnManager::CheckRum(TArray<FString> cocName, bool bStirred, bool bStirredLater, bool bShaked, TArray<bool> garnishArray,  int32 customerIdx)
{
	// 다이커리 판정
	if(amountOfLime > 0)
	{
		if(cocName.Num() == Daiquiri.Num())
		{
			if(bStirred != false && bStirredLater != true)
			{
				orderScore -= 0;
			}
			else if(bStirred != false && bStirredLater != false)
			{
				orderScore -= 10;
			}
			else
			{
				orderScore -= 25;

				scoreIdx[2] = 1;
			}

			if(bShaked != false)
			{
				orderScore -= 0;
			}
			else
			{
				orderScore -= 25;

				scoreIdx[2] = 1;
			}

			if(garnishArray[0] == true)
			{
				orderScore -= 0;
			}
			else
			{
				orderScore -= 10;
			}
			
			CheckDaiquiri(customerIdx);
		}		
	}
	// 레시피 범위 밖
	else
	{
		SomethingElse(customerIdx);
	}
}

void ASpawnManager::CheckGinLime(int32 customerIdx)
{
	float ginLime = amountOfLime + amountOfGin;

	float ginRatio = amountOfGin/ginLime;

	float limeRatio = amountOfLime/ginLime;
	
	if(ginRatio > 0.71 && ginRatio < 0.79)
	{
		orderScore -= 0;
	}
	else if(ginRatio > 0.6 && ginRatio <= 0.71)
	{
		orderScore -= 15;
	}
	else if(ginRatio < 0.9 && ginRatio >= 0.79)
	{
		orderScore -= 15;
	}
	else
	{
		orderScore -= 25;

		scoreIdx[0] = 1;
	}

	if(limeRatio > 0.23 && limeRatio < 0.27)
	{
		orderScore -= 0;
	}
	else if(limeRatio > 0.2 && limeRatio <= 0.23)
	{
		orderScore -= 15;
	}
	else if(limeRatio < 0.3 && limeRatio >= 0.27)
	{
		orderScore -= 15;
	}
	else
	{
		orderScore -= 25;

		scoreIdx[0] = 1;
	}

	if(ginLime > 1.9 && ginLime < 2.1)
	{
		orderScore -= 0;
	}
	else if(ginLime > 1.8 && ginLime <= 1.9)
	{
		orderScore -= 10;
	}
	else if(ginLime < 2.2 && ginLime >= 2.1)
	{
		orderScore -= 10;
	}
	else
	{
		orderScore -= 20;

		scoreIdx[1] = 1;
	}

	if(gi->checkDayCount == 1)
	{
		orderCoctailIdx[customerIdx] = 1;
	}
	else
	{
		if(orderCoctailIdx[customerIdx] == 1)
		{
			aChairs[customerIdx]->ViewScore(orderScore);

			aChairs[customerIdx]->SameOrder();
		}
		else
		{
			aChairs[customerIdx]->UnSameOrder();
		}
	}
}

void ASpawnManager::CheckMartini(int32 customerIdx)
{
	float martini = amountOfVermouth + amountOfGin;

	float ginRatio = amountOfGin/martini;

	float vermouthRatio = amountOfVermouth/martini;
	
	if(ginRatio > 0.82 && ginRatio < 0.9)
	{
		orderScore -= 0;
	}
	else if(ginRatio > 0.77 && ginRatio <= 0.82)
	{
		orderScore -= 15;
	}
	else if(ginRatio < 0.95 && ginRatio >= 0.9)
	{
		orderScore -= 15;
	}
	else
	{
		orderScore -= 25;

		scoreIdx[0] = 1;
	}

	if(vermouthRatio > 0.13 && vermouthRatio < 0.15)
	{
		orderScore -= 0;
	}
	else if(vermouthRatio > 0.12 && vermouthRatio <= 0.13)
	{
		orderScore -= 15;
	}
	else if(vermouthRatio < 0.16 && vermouthRatio >= 0.15)
	{
		orderScore -= 15;
	}
	else
	{
		orderScore -= 25;

		scoreIdx[0] = 1;
	}

	if(martini > 2.1 && martini < 2.6)
	{
		orderScore -= 0;
	}
	else if(martini > 2.0 && martini <= 2.1)
	{
		orderScore -= 5;
	}
	else if(martini < 2.7 && martini >= 2.6)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 10;

		scoreIdx[1] = 1;
	}

	if(gi->checkDayCount == 1)
	{
		orderCoctailIdx[customerIdx] = 3;
	}
	else
	{
		if(orderCoctailIdx[customerIdx] == 3)
		{
			aChairs[customerIdx]->ViewScore(orderScore);

			aChairs[customerIdx]->SameOrder();
		}
		else
		{
			aChairs[customerIdx]->UnSameOrder();
		}
	}
}

void ASpawnManager::CheckDaiquiri(int32 customerIdx)
{
	float daiquiri = amountOfLime + amountOfRum + amountOfSugar;

	float rumRatio = amountOfRum/daiquiri;

	float limeRatio = amountOfLime/daiquiri;

	float sugarRatio = amountOfSugar/daiquiri;
	
	if(rumRatio > 0.61 && rumRatio < 0.71)
	{
		orderScore -= 0;
	}
	else if(rumRatio > 0.56 && rumRatio <= 0.61)
	{
		orderScore -= 5;
	}
	else if(rumRatio < 0.76 && rumRatio >= 0.71)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 10;

		scoreIdx[0] = 1;
	}

	if(sugarRatio > 0.09 && sugarRatio < 0.13)
	{
		orderScore -= 0;
	}
	else if(sugarRatio > 0.07 && sugarRatio <= 0.09)
	{
		orderScore -= 5;
	}
	else if(sugarRatio < 0.15 && sugarRatio >= 0.13)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 10;

		scoreIdx[0] = 1;
	}

	if(limeRatio > 0.18 && limeRatio < 0.26)
	{
		orderScore -= 0;
	}
	else if(limeRatio > 0.15 && limeRatio <= 0.18)
	{
		orderScore -= 5;
	}
	else if(limeRatio < 0.29 && limeRatio >= 0.26)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 10;

		scoreIdx[0] = 1;
	}

	if(daiquiri > 2.5 && daiquiri < 2.8)
	{
		orderScore -= 0;
	}
	else if(daiquiri > 2.4 && daiquiri <= 2.5)
	{
		orderScore -= 5;
	}
	else if(daiquiri < 3.0 && daiquiri >= 2.8)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 10;

		scoreIdx[1] = 1;
	}

	if(gi->checkDayCount == 1)
	{
		orderCoctailIdx[customerIdx] = 2;
	}
	else
	{
		if(orderCoctailIdx[customerIdx] == 2)
		{
			aChairs[customerIdx]->ViewScore(orderScore);

			aChairs[customerIdx]->SameOrder();
		}
		else
		{
			aChairs[customerIdx]->UnSameOrder();
		}
	}
}

void ASpawnManager::CheckNegroni(int32 customerIdx)
{
	float negroni = amountOfGin + amountOfCampari + amountOfVermouth;

	float ginRatio = amountOfGin/negroni;

	float campariRatio = amountOfCampari/negroni;

	float vermouthRatio = amountOfVermouth/negroni;

	if(ginRatio > 0.31 && ginRatio < 0.35)
	{
		orderScore -= 0;
	}
	else if(ginRatio > 0.3 && ginRatio <= 0.31)
	{
		orderScore -= 5;
	}
	else if(ginRatio < 0.36 && ginRatio >= 0.35)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 20;

		scoreIdx[0] = 1;
	}

	if(vermouthRatio > 0.31 && vermouthRatio < 0.35)
	{
		orderScore -= 0;
	}
	else if(vermouthRatio > 0.3 && vermouthRatio <= 0.31)
	{
		orderScore -= 5;
	}
	else if(vermouthRatio < 0.36 && vermouthRatio >= 0.35)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 20;

		scoreIdx[0] = 1;
	}

	if(campariRatio > 0.31 && campariRatio < 0.35)
	{
		orderScore -= 0;
	}
	else if(campariRatio > 0.3 && campariRatio <= 0.31)
	{
		orderScore -= 5;
	}
	else if(campariRatio < 0.36 && campariRatio >= 0.35)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 20;

		scoreIdx[0] = 1;
	}

	if(negroni > 2.85 && negroni < 3.15)
	{
		orderScore -= 0;
	}
	else if(negroni > 2.7 && negroni <= 2.85)
	{
		orderScore -= 5;
	}
	else if(negroni < 3.3 && negroni >= 3.15)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 20;

		scoreIdx[1] = 1;
	}

	if(gi->checkDayCount == 1)
	{
		orderCoctailIdx[customerIdx] = 4;
	}
	else
	{
		if(orderCoctailIdx[customerIdx] == 4)
		{
			aChairs[customerIdx]->ViewScore(orderScore);

			aChairs[customerIdx]->SameOrder();
		}
		else
		{
			aChairs[customerIdx]->UnSameOrder();
		}
	}
}

void ASpawnManager::CheckOldPal(int32 customerIdx)
{
	float oldPal = amountOfCampari + amountOfVermouth + amountOfWhiskey;

	float whiskyRatio = amountOfWhiskey/oldPal;

	float vermouthRatio = amountOfVermouth/oldPal;

	float campariRatio = amountOfCampari/oldPal;
	
	if(whiskyRatio > 0.31 && whiskyRatio < 0.35)
	{
		orderScore -= 0;
	}
	else if(whiskyRatio > 0.3 && whiskyRatio <= 0.31)
	{
		orderScore -= 5;
	}
	else if(whiskyRatio < 0.36 && whiskyRatio >= 0.35)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 20;
	}

	if(vermouthRatio > 0.31 && vermouthRatio < 0.35)
	{
		orderScore -= 0;
	}
	else if(vermouthRatio > 0.3 && vermouthRatio <= 0.31)
	{
		orderScore -= 5;
	}
	else if(vermouthRatio < 0.36 && vermouthRatio >= 0.35)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 20;
	}

	if(campariRatio > 0.31 && campariRatio < 0.35)
	{
		orderScore -= 0;
	}
	else if(campariRatio > 0.3 && campariRatio <= 0.31)
	{
		orderScore -= 5;
	}
	else if(campariRatio < 0.36 && campariRatio >= 0.35)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 20;
	}

	if(oldPal > 2.85 && oldPal < 3.15)
	{
		orderScore -= 0;
	}
	else if(oldPal > 2.7 && oldPal <= 2.85)
	{
		orderScore -= 5;
	}
	else if(oldPal < 3.3 && oldPal >= 3.15)
	{
		orderScore -= 5;
	}
	else
	{
		orderScore -= 10;
	}

	if(gi->checkDayCount == 1)
	{
		SomethingElse(customerIdx);
	}
	else
	{
		if(orderCoctailIdx[customerIdx] == 5)
		{
			if(bSpawnOld == true)
			{
				aChairs[customerIdx]->SameOrder();
			}
		}
		else
		{
			aChairs[customerIdx]->UnSameOrder();
		}
	}
}


void ASpawnManager::SomethingElse(int32 customerIdx)
{
	if(gi->checkDayCount == 1)
	{
		orderCoctailIdx[customerIdx] = 6;
	}
	else
	{
		aChairs[customerIdx]->UnSameOrder();
	}
}