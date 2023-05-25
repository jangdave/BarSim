// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalOrderWidget.h"
#include "Components/TextBlock.h"

void UOldPalOrderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
	
	oldpalScript1.Emplace(FString::Printf(TEXT("그러지 말고, 단골인데 한 잔 만들어 주지 그래?"))); // 0
	//---------------------------------------------------------------------------선택
	// 어떤 선택지 이든 답변
	oldpalScript1.Emplace(FString::Printf(TEXT("아무 칵테일이나 좋으니 자신있는 걸로 하나 만들어 주게나"))); // 1
	// 혼잣말
	oldpalScript1.Emplace(FString::Printf(TEXT("이제는 여기 계단 내려오는 것도 힘이 들군"))); // 2
	oldpalScript1.Emplace(FString::Printf(TEXT("그래도 역시 뭘 마실땐, 여기 올드팔이 제일 편해"))); // 3
	oldpalScript1.Emplace(FString::Printf(TEXT("새삼 이 곳도 정말 오래된 친구 같아졌군 그래 허허"))); // 4
	//---------------------------------------------------------------------------선택
	oldpalScript1.Emplace(FString::Printf(TEXT("진라임... 인건가"))); // 5
	oldpalScript1.Emplace(FString::Printf(TEXT("다이커리... 인건가"))); // 6
	oldpalScript1.Emplace(FString::Printf(TEXT("마티니... 인건가"))); // 7
	//---------------------------------------------------------------------------
	oldpalScript1.Emplace(FString::Printf(TEXT("조금 덜 성숙한 맛이 나긴 하지만 나쁘지 않군"))); // 8
	//---------------------------------------------------------------------------선택
	oldpalScript1.Emplace(FString::Printf(TEXT("다음 번에는 비율에 더 신경써서 만들면 더할 나위 없겠군"))); // 9
	oldpalScript1.Emplace(FString::Printf(TEXT("다음 번에는 양에 더 신경써서 만들면 더할 나위 없겠군"))); // 10
	oldpalScript1.Emplace(FString::Printf(TEXT("다음 번에는 기법에 더 신경써서 만들면 더할 나위 없겠군"))); // 11
	//---------------------------------------------------------------------------
	oldpalScript1.Emplace(FString::Printf(TEXT("오늘은 한잔만 마시고 가보겠네"))); // 12
	oldpalScript1.Emplace(FString::Printf(TEXT("또 보세 젊은 바텐더 선생"))); // 13
	
}

void UOldPalOrderWidget::SetOldPalText(int32 idx)
{
	text_oldpal->SetText(FText::FromString(oldpalScript1[idx]));
}