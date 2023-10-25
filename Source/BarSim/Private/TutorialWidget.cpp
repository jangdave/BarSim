// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"

#include <Components/TextBlock.h>

#include "BarGameInstance.h"
#include "Components/CheckBox.h"
#include "Components/WidgetSwitcher.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(0);
}

void UTutorialWidget::SetWelcome()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(1);
}

void UTutorialWidget::SetFirst()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(2);
}

void UTutorialWidget::SetSecond()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(3);
}

void UTutorialWidget::SetThird()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(4);
}

void UTutorialWidget::SetFourth()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(5);
}

void UTutorialWidget::SetCheckCup()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(6);
}

void UTutorialWidget::SetCheckTablet()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(7);
}

void UTutorialWidget::SetCheckNext()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(8);
}

void UTutorialWidget::SetFirst1Check()
{
	checkFirst1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFirst2Check()
{
	checkFirst2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFirst3Check()
{
	checkFirst3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond1Check()
{
	checkSecond1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond2Check()
{
	checkSecond2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetSecond3Check()
{
	checkSecond3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetThird1Check()
{
	checkThird1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetThird2Check()
{
	checkThird2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetThird3Check()
{
	checkThird3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth1Check()
{
	checkFourth1->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth2Check()
{
	checkFourth2->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth3Check()
{
	checkFourth3->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth4Check()
{
	checkFourth4->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetFourth5Check()
{
	checkFourth5->SetCheckedState(ECheckBoxState::Checked);
}

void UTutorialWidget::SetLanguageEnglish()
{
	text_MoveToArea->SetText(FText::FromString("Move into the zone."));
	text_Quest1->SetText(FText::FromString("Put 3 ice cubes into a cup using tongs."));
	text_Quest2->SetText(FText::FromString("Grab a bottle and fill a cup with 2oz of alcohol."));
	text_Quest3->SetText(FText::FromString("Use tongs to place 1 lime slice into a cup."));
	text_Quest4->SetText(FText::FromString("Grab a bottle and fill the mixing glass, 3oz."));
	text_Quest5->SetText(FText::FromString("Hold bar spoon, stir inside mixing glass 5 times."));
	text_Quest6->SetText(FText::FromString("Fit strainer to mixing glass and fill cup at least 2oz."));
	text_Quest7->SetText(FText::FromString("Grab a bottle and fill the shaker with 3oz of alcohol."));
	text_Quest8->SetText(FText::FromString("Install the strainer and lid in order and shake for 10 sec."));
	text_Quest9->SetText(FText::FromString("Remove the lid of the shaker and pour 2oz into the cup."));
	text_Quest10->SetText(FText::FromString("Place the cup in the green area to the next step."));
	text_Quest11->SetText(FText::FromString("Place the tablet in the green area to the next step."));
	text_Quest12->SetText(FText::FromString("Move to the right."));
	text_Quest13->SetText(FText::FromString("Run the recipe app."));
	text_Quest14->SetText(FText::FromString("You can learn the recipes of various cocktails."));
	text_Quest15->SetText(FText::FromString("Run the mail app."));
	text_Quest16->SetText(FText::FromString("Look through the story of Brandon's arrival at Old Pal."));
	text_Quest17->SetText(FText::FromString("Run the Internet app."));
	text_Quest18->SetText(FText::FromString("You can enter it on your keyboard to go to the address you want."));
	text_Quest19->SetText(FText::FromString("Press the Start Sales button."));
	text_Quest20->SetText(FText::FromString("If you press the Start Business button at the bar, the customer will enter."));
	text_Quest21->SetText(FText::FromString("Press the closing button."));
	text_Quest22->SetText(FText::FromString("If no more customers come, press the closing button to close the bar."));
}

void UTutorialWidget::SetLanguageKorean()
{
	KorLanguageArray.Emplace(FString::Printf(TEXT("영역 안으로 이동하세요."))); //0
	KorLanguageArray.Emplace(FString::Printf(TEXT("집게를 사용하여 컵에 얼음을 3개 넣으세요."))); //1
	KorLanguageArray.Emplace(FString::Printf(TEXT("술병을 잡아 컵에 술을 2oz 이상 채우세요."))); //2
	KorLanguageArray.Emplace(FString::Printf(TEXT("집게를 사용하여 라임 슬라이스를 컵에 1개 넣으세요."))); //3
	KorLanguageArray.Emplace(FString::Printf(TEXT("술병을 잡아 믹싱 글래스에 3oz 이상 채우세요."))); //4
	KorLanguageArray.Emplace(FString::Printf(TEXT("바 스푼을 잡고 믹싱 글래스 내부를 5번 저으세요."))); //5
	KorLanguageArray.Emplace(FString::Printf(TEXT("믹싱 글래스에 스트레이너를 장착하고 컵에 2oz 이상 채우세요."))); //6
	KorLanguageArray.Emplace(FString::Printf(TEXT("술병을 잡아 쉐이커에 술을 3oz 이상 채우세요."))); //7
	KorLanguageArray.Emplace(FString::Printf(TEXT("스트레이너와 뚜껑을 순서대로 장착하고 10초 이상 흔들어주세요."))); //8
	KorLanguageArray.Emplace(FString::Printf(TEXT("쉐이커의 뚜껑을 분리시키고 컵에 2oz 이상 따르세요."))); //9
	KorLanguageArray.Emplace(FString::Printf(TEXT("컵을 초록색 영역에 놓으면 다음 단계로 넘어갑니다."))); //10
	KorLanguageArray.Emplace(FString::Printf(TEXT("태블릿을 초록색 영역에 놓으면 다음 단계로 넘어갑니다."))); //11
	KorLanguageArray.Emplace(FString::Printf(TEXT("오른쪽으로 이동하세요."))); //12
	KorLanguageArray.Emplace(FString::Printf(TEXT("레시피 앱을 실행하세요."))); //13
	KorLanguageArray.Emplace(FString::Printf(TEXT("다양한 칵테일의 레시피를 익힐 수 있습니다."))); //14
	KorLanguageArray.Emplace(FString::Printf(TEXT("메일 앱을 실행하세요."))); //15
	KorLanguageArray.Emplace(FString::Printf(TEXT("브랜든이 올드 팔에 오기까지의 이야기를 훑어보세요."))); //16
	KorLanguageArray.Emplace(FString::Printf(TEXT("인터넷 앱을 실행하세요."))); //17
	KorLanguageArray.Emplace(FString::Printf(TEXT("키보드로 입력해 원하는 주소로 이동할 수 있습니다."))); //18
	KorLanguageArray.Emplace(FString::Printf(TEXT("영업 시작 버튼을 누르세요."))); //19
	KorLanguageArray.Emplace(FString::Printf(TEXT("바에서 영업 시작 버튼을 누르면 손님이 입장합니다."))); //20
	KorLanguageArray.Emplace(FString::Printf(TEXT("영업 마감 버튼을 누르세요."))); //21
	KorLanguageArray.Emplace(FString::Printf(TEXT("손님이 더 오지 않는다면 영업 마감 버튼을 눌러 영업을 종료하세요."))); //22
	text_MoveToArea->SetText(FText::FromString(KorLanguageArray[0]));
	text_Quest1->SetText(FText::FromString(KorLanguageArray[1]));
	text_Quest2->SetText(FText::FromString(KorLanguageArray[2]));
	text_Quest3->SetText(FText::FromString(KorLanguageArray[3]));
	text_Quest4->SetText(FText::FromString(KorLanguageArray[4]));
	text_Quest5->SetText(FText::FromString(KorLanguageArray[5]));
	text_Quest6->SetText(FText::FromString(KorLanguageArray[6]));
	text_Quest7->SetText(FText::FromString(KorLanguageArray[7]));
	text_Quest8->SetText(FText::FromString(KorLanguageArray[8]));
	text_Quest9->SetText(FText::FromString(KorLanguageArray[9]));
	text_Quest10->SetText(FText::FromString(KorLanguageArray[10]));
	text_Quest11->SetText(FText::FromString(KorLanguageArray[11]));
	text_Quest12->SetText(FText::FromString(KorLanguageArray[12]));
	text_Quest13->SetText(FText::FromString(KorLanguageArray[13]));
	text_Quest14->SetText(FText::FromString(KorLanguageArray[14]));
	text_Quest15->SetText(FText::FromString(KorLanguageArray[15]));
	text_Quest16->SetText(FText::FromString(KorLanguageArray[16]));
	text_Quest17->SetText(FText::FromString(KorLanguageArray[17]));
	text_Quest18->SetText(FText::FromString(KorLanguageArray[18]));
	text_Quest19->SetText(FText::FromString(KorLanguageArray[19]));
	text_Quest20->SetText(FText::FromString(KorLanguageArray[20]));
	text_Quest21->SetText(FText::FromString(KorLanguageArray[21]));
	text_Quest22->SetText(FText::FromString(KorLanguageArray[22]));

}
