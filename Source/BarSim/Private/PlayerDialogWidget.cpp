// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDialogWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UPlayerDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
	
	playerScript1.Emplace(FString::Printf(TEXT("손님 오늘은 내부 사정으로 영업하지 않습니다"))); // 0
	//---------------------------------------------------------------------------선택
	// 만들어 준다
	playerScript1.Emplace(FString::Printf(TEXT("...알겠습니다 일단 자리에 앉으시죠"))); // 1
	// 안만들어 준다
	playerScript1.Emplace(FString::Printf(TEXT("...죄송합니다 내일 방문해 주시죠"))); // 2
	// 결국 앉음
	playerScript1.Emplace(FString::Printf(TEXT("(이상한 손님이군 적당히 아무 칵테일이나 만들어 주자)"))); // 3
	// 칵테일 나옴
	playerScript1.Emplace(FString::Printf(TEXT("여기 칵테일 나왔습니다"))); // 4
	playerScript1.Emplace(FString::Printf(TEXT("별난 손님이였군...."))); // 5
	playerScript1.Emplace(FString::Printf(TEXT("(오랜만에 만든거 치곤 나쁘지 않았나 보다)"))); // 6
	playerScript1.Emplace(FString::Printf(TEXT("오늘은 이만 집으로 돌아가자"))); // 7

	// 1번째 선택지
	playerChoice1.Emplace(FString::Printf(TEXT("손님을 받을까?"))); // 0
	playerChoice1.Emplace(FString::Printf(TEXT("받는다"))); // 1
	playerChoice1.Emplace(FString::Printf(TEXT("받지 않는다"))); // 2
}

void UPlayerDialogWidget::SetSwitcher(int32 idx)
{
	WidgetSwitcher_Player->SetActiveWidgetIndex(idx);
}

void UPlayerDialogWidget::SetPlayerText(int32 idx)
{
	text_Player->SetText(FText::FromString(playerScript1[idx]));
}

void UPlayerDialogWidget::SetChoice1()
{
	text_Choice->SetText(FText::FromString(playerChoice1[0]));
	text_Left->SetText(FText::FromString(playerChoice1[1]));
	text_Right->SetText(FText::FromString(playerChoice1[2]));
}