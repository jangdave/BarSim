// Fill out your copyright notice in the Description page of Project Settings.


#include "CoctailScoreWidget.h"

#include <Components/TextBlock.h>

#include "BarGameInstance.h"
#include "Components/WidgetSwitcher.h"

void UCoctailScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	gi = Cast<UBarGameInstance>(GetGameInstance());

	SetLanguage();
}

void UCoctailScoreWidget::SetLanguage()
{
	if(gi)
	{
		// Language Setting = Korean
		if(gi->bEnglish==false)
		{
			cleanGuideScriptArray.Emplace(FString::Printf(TEXT("컵과 코스터를 수거하세요"))); // 0
			cleanGuideScriptArray.Emplace(FString::Printf(TEXT("사용한 컵은 싱크대에서 비우세요"))); // 1
			text_CleanGuide1->SetText(FText::FromString(cleanGuideScriptArray[0]));
			text_CleanGuide2->SetText(FText::FromString(cleanGuideScriptArray[1]));
		}
		// Language Setting = English
		else
		{
			text_CleanGuide1->SetText(FText::FromString("Remove cups and coasters."));
			text_CleanGuide2->SetText(FText::FromString("Empty the cup in the sink."));			
		}
	}
}

void UCoctailScoreWidget::SetScoreSwitcher(int32 idx)
{
	WidgetSwitcher_scoreBox->SetActiveWidgetIndex(idx);
}
