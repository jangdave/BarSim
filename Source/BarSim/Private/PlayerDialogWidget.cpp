// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDialogWidget.h"

#include "BarGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UPlayerDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::Hidden);

	gi = Cast<UBarGameInstance>(GetGameInstance());
	
	btn_Left->OnClicked.AddDynamic(this, &UPlayerDialogWidget::LeftAnswer);
	btn_Right->OnClicked.AddDynamic(this, &UPlayerDialogWidget::RightAnswer);

	SetLanguage();
}

void UPlayerDialogWidget::SetSwitcher(int32 idx)
{
	WidgetSwitcher_Player->SetActiveWidgetIndex(idx);
}

void UPlayerDialogWidget::SetPlayerText(int32 idx)
{
	if(gi->checkDayCount == 1)
	{
		text_Player->SetText(FText::FromString(playerScript1[idx]));
	}
	else if(gi->checkDayCount == 2)
	{
		text_Player->SetText(FText::FromString(playerScript2[idx]));
	}
	else if(gi->checkDayCount == 3)
	{
		text_Player->SetText(FText::FromString(playerScript3[idx]));
	}
}

void UPlayerDialogWidget::SetChoice1()
{
	text_Left->SetText(FText::FromString(playerChoice1[0]));
	text_Right->SetText(FText::FromString(playerChoice1[1]));
}

void UPlayerDialogWidget::SetChoice2()
{
	text_Left->SetText(FText::FromString(playerChoice2[0]));
	text_Right->SetText(FText::FromString(playerChoice2[1]));
}

void UPlayerDialogWidget::SetChoice3()
{
	text_Left->SetText(FText::FromString(playerChoice3[0]));
	text_Right->SetText(FText::FromString(playerChoice3[1]));
}

void UPlayerDialogWidget::LeftAnswer()
{
	choiceCount = 1;
}

void UPlayerDialogWidget::RightAnswer()
{
	choiceCount = 2;
}

void UPlayerDialogWidget::StartPlayerText(int32 idx)
{
	text_Player->SetText(FText::FromString(playerStartScript[idx]));
}

void UPlayerDialogWidget::SetLanguage()
{
	if(gi)
	{
		// Language Setting = Korean
		if(gi->bEnglish==false)
		{
			// 첫째날 대사
			playerScript1.Emplace(FString::Printf(TEXT("손님, 오늘은 내부 사정으로 영업하지 않습니다"))); // 0
			//---------------------------------------------------------------------------선택
			// 선택지 1
			playerScript1.Emplace(FString::Printf(TEXT("...알겠습니다"))); // 1
			// 선택지 2
			playerScript1.Emplace(FString::Printf(TEXT("일단 앉으시죠"))); // 2
			// 앉고 나서
			playerScript1.Emplace(FString::Printf(TEXT("(이상한 손님이군... 어쨌든 손님이 왔으니 코스터를 제공해주자)"))); // 3
			// 칵테일 나옴
			playerScript1.Emplace(FString::Printf(TEXT("여기 주문하신 칵테일 나왔습니다"))); // 4
			playerScript1.Emplace(FString::Printf(TEXT("별난 손님이였군...."))); // 5
			playerScript1.Emplace(FString::Printf(TEXT("(오랜만에 만든거 치곤 나쁘지 않았나 보다)"))); // 6
			playerScript1.Emplace(FString::Printf(TEXT("오늘은 이만 집으로 돌아가자"))); // 7

			// 1번째 선택지
			playerChoice1.Emplace(FString::Printf(TEXT("...알겠습니다"))); // 0
			playerChoice1.Emplace(FString::Printf(TEXT("일단 앉으시죠"))); // 1

			// 둘째날 대사
			playerScript2.Emplace(FString::Printf(TEXT("오늘도 어찌저찌 하루를 마무리 했군"))); // 0
			playerScript2.Emplace(FString::Printf(TEXT("설마 어제의 별난 손님은 오지 않겠지..."))); // 1
			playerScript2.Emplace(FString::Printf(TEXT("마감하고 돌아가자"))); // 2

			// 셋째날 대사
			playerScript3.Emplace(FString::Printf(TEXT("손님...또 영업시간이 끝나고 오셨군요"))); // 0
			playerScript3.Emplace(FString::Printf(TEXT("제 시간에 와주시면 안될까요?"))); // 1
			playerScript3.Emplace(FString::Printf(TEXT("알겠습니다. 오늘까지만 받아드릴게요"))); // 2
			playerScript3.Emplace(FString::Printf(TEXT("그럼 주문은 어떤걸로 드릴까요"))); // 3
			playerScript3.Emplace(FString::Printf(TEXT("음...올드팔은 만들어 본 적이 없네요"))); // 4
			playerScript3.Emplace(FString::Printf(TEXT("다음 영업일에 오시면 연습해두겠습니다"))); // 5
			playerScript3.Emplace(FString::Printf(TEXT("오늘은 그럼 이만..."))); // 6
			playerScript3.Emplace(FString::Printf(TEXT("이런, 레시피도 외우고 계세요?"))); // 7
			playerScript3.Emplace(FString::Printf(TEXT("알겠습니다, 만들어 드리죠"))); // 8
			playerScript3.Emplace(FString::Printf(TEXT("자리에 앉으시죠"))); // 9
			playerScript3.Emplace(FString::Printf(TEXT("(정말 까다로운 손님이군...)"))); // 10
			playerScript3.Emplace(FString::Printf(TEXT("아...역시 아버지의 단골이셨군요"))); // 11
			playerScript3.Emplace(FString::Printf(TEXT("제 이름을 말씀드렸던가요...?"))); // 12
			playerScript3.Emplace(FString::Printf(TEXT("아! 저한테 메일을 보내셨던 그...아버지의 친구분?"))); // 13
			playerScript3.Emplace(FString::Printf(TEXT("아닙니다. 뭐...오랜 친구분이시면 그럴수 있죠"))); // 14
			playerScript3.Emplace(FString::Printf(TEXT("사실 서로 연락이 안된지 오래됐고, 서로 관심도 없었습니다"))); // 15
			playerScript3.Emplace(FString::Printf(TEXT("가게도 잠시만 운영하고 정리할 생각이라..."))); // 16
			playerScript3.Emplace(FString::Printf(TEXT("손님, 아니 리차드 아저씨께는 죄송하게 됐네요"))); // 17
			playerScript3.Emplace(FString::Printf(TEXT("내기요...? 어떤?"))); // 18
			playerScript3.Emplace(FString::Printf(TEXT("그게 무슨...?"))); // 19
			playerScript3.Emplace(FString::Printf(TEXT("아저씨가 어떤 칵테일을 만들어 달라고 할 줄 알고요?"))); // 20
			playerScript3.Emplace(FString::Printf(TEXT("터무니 없어요... 말도 안된다구요"))); // 21
			playerScript3.Emplace(FString::Printf(TEXT("(말이 안되는 요구이지만 지금은 마땅한 일도 없고...)"))); // 22
			playerScript3.Emplace(FString::Printf(TEXT("...알겠습니다"))); // 23
			playerScript3.Emplace(FString::Printf(TEXT("어쩔 수 없죠"))); // 24
			playerScript3.Emplace(FString::Printf(TEXT("...아버지가 저를 생각하면서요? 말도 안돼요"))); // 25
			playerScript3.Emplace(FString::Printf(TEXT("그렇게 연락 한 통 없던, 빌어먹을 아버지였는데요?"))); // 26
			playerScript3.Emplace(FString::Printf(TEXT("이제와서 그런다고 도대체 뭐가 달라지죠?"))); // 27
			playerScript3.Emplace(FString::Printf(TEXT("젓지 말고, 흔들어서 라... 익숙한 문장인데"))); // 28
			playerScript3.Emplace(FString::Printf(TEXT("일단 오늘은 여기까지 하자"))); // 29
			playerScript3.Emplace(FString::Printf(TEXT("빌어먹을 아버지..."))); // 30
			playerScript3.Emplace(FString::Printf(TEXT("어떤 생각을 했는지 한 번 들어나보자고"))); // 31
	
			// 2번째 선택지
			playerChoice2.Emplace(FString::Printf(TEXT("알겠습니다"))); // 0
			playerChoice2.Emplace(FString::Printf(TEXT("앉으시죠"))); // 1

			// 3번째 선택지
			playerChoice3.Emplace(FString::Printf(TEXT("...알겠습니다"))); // 0
			playerChoice3.Emplace(FString::Printf(TEXT("어쩔 수 없죠"))); // 1

			// 시작 대사
			playerStartScript.Emplace(FString::Printf(TEXT("문을 열고 바 올드 팔로 이동하세요"))); // 0
			playerStartScript.Emplace(FString::Printf(TEXT("여기가 올드팔...이군"))); // 1
			playerStartScript.Emplace(FString::Printf(TEXT("어제 온 손님은 오늘 안오겠지. 문을 열고 내려가자"))); // 2
			playerStartScript.Emplace(FString::Printf(TEXT("3일째가 되니 슬슬 익숙해지는군. 문을 열고 내려가자"))); // 3
		}
		// Language Setting = English
		else
		{
			// 첫째날 대사
			playerScript1.Emplace(FString::Printf(TEXT("Sir, we are closed today due to internal circumstances."))); // 0
			//---------------------------------------------------------------------------선택
			// 선택지 1
			playerScript1.Emplace(FString::Printf(TEXT("... All right, sir."))); // 1
			// 선택지 2
			playerScript1.Emplace(FString::Printf(TEXT("Please sit down..."))); // 2
			// 앉고 나서
			playerScript1.Emplace(FString::Printf(TEXT("(Let's give him a coaster.)"))); // 3
			// 칵테일 나옴
			playerScript1.Emplace(FString::Printf(TEXT("Here is your cocktail."))); // 4
			playerScript1.Emplace(FString::Printf(TEXT("What a strange man...?"))); // 5
			playerScript1.Emplace(FString::Printf(TEXT("(I guess the cocktail wasn't bad.)"))); // 6
			playerScript1.Emplace(FString::Printf(TEXT("Let's go home now."))); // 7

			// 1번째 선택지
			playerChoice1.Emplace(FString::Printf(TEXT("... All right."))); // 0
			playerChoice1.Emplace(FString::Printf(TEXT("Please sit..."))); // 1

			// 둘째날 대사
			playerScript2.Emplace(FString::Printf(TEXT("Ended the day somehow."))); // 0
			playerScript2.Emplace(FString::Printf(TEXT("Don't tell me yesterday's strange man will come..."))); // 1
			playerScript2.Emplace(FString::Printf(TEXT("Let's close the day and go back."))); // 2

			// 셋째날 대사
			playerScript3.Emplace(FString::Printf(TEXT("Sir... You're here again after business hours..."))); // 0
			playerScript3.Emplace(FString::Printf(TEXT("Could you please come on time?"))); // 1
			playerScript3.Emplace(FString::Printf(TEXT("All right... It's only today, Sir."))); // 2
			playerScript3.Emplace(FString::Printf(TEXT("Then... what would you like to order?"))); // 3
			playerScript3.Emplace(FString::Printf(TEXT("Well... I've never made Old Pal before."))); // 4
			playerScript3.Emplace(FString::Printf(TEXT("If you come next time, I'm gonna practice it."))); // 5
			playerScript3.Emplace(FString::Printf(TEXT("Then, today..."))); // 6
			playerScript3.Emplace(FString::Printf(TEXT("Jeez... do you even know the recipe?"))); // 7
			playerScript3.Emplace(FString::Printf(TEXT("Okay, Sir. I'm gonna try it for you."))); // 8
			playerScript3.Emplace(FString::Printf(TEXT("Please have a seat."))); // 9
			playerScript3.Emplace(FString::Printf(TEXT("(Such a picky customer...)"))); // 10
			playerScript3.Emplace(FString::Printf(TEXT("Ah... as expected, you were my father's regular."))); // 11
			playerScript3.Emplace(FString::Printf(TEXT("Did I... tell you my name...?"))); // 12
			playerScript3.Emplace(FString::Printf(TEXT("Oh...! The person who sent me the email...? Father's friend...?"))); // 13
			playerScript3.Emplace(FString::Printf(TEXT("No, it's okay... that's possible..."))); // 14
			playerScript3.Emplace(FString::Printf(TEXT("Actually, we haven't been in touch for a long time."))); // 15
			playerScript3.Emplace(FString::Printf(TEXT("I'm gonna run the store for a while... and clean it up..."))); // 16
			playerScript3.Emplace(FString::Printf(TEXT("I'm sorry, sir... um... Richard."))); // 17
			playerScript3.Emplace(FString::Printf(TEXT("A bet...? for what...?"))); // 18
			playerScript3.Emplace(FString::Printf(TEXT("What... the...?"))); // 19
			playerScript3.Emplace(FString::Printf(TEXT("How could I know which cocktail you're gonna ask for...?"))); // 20
			playerScript3.Emplace(FString::Printf(TEXT("Ridiculous... I can't believe it...!"))); // 21
			playerScript3.Emplace(FString::Printf(TEXT("(It's a ridiculous demand, but there's no other way...)"))); // 22
			playerScript3.Emplace(FString::Printf(TEXT("... I see."))); // 23
			playerScript3.Emplace(FString::Printf(TEXT("... There's no other way..."))); // 24
			playerScript3.Emplace(FString::Printf(TEXT("... My father thinks of me...? No way..."))); // 25
			playerScript3.Emplace(FString::Printf(TEXT("... damn father who even didn't call me just once?"))); // 26
			playerScript3.Emplace(FString::Printf(TEXT("What the heck does that change now?"))); // 27
			playerScript3.Emplace(FString::Printf(TEXT("Shaken, Not Stirred... it sounds familiar..."))); // 28
			playerScript3.Emplace(FString::Printf(TEXT("Let's stop here for today."))); // 29
			playerScript3.Emplace(FString::Printf(TEXT("Damn father..."))); // 30
			playerScript3.Emplace(FString::Printf(TEXT("Let me just hear what the heck you thought."))); // 31
	
			// 2번째 선택지
			playerChoice2.Emplace(FString::Printf(TEXT("Okay, Sir."))); // 0
			playerChoice2.Emplace(FString::Printf(TEXT("Please have a seat."))); // 1

			// 3번째 선택지
			playerChoice3.Emplace(FString::Printf(TEXT("...I see"))); // 0
			playerChoice3.Emplace(FString::Printf(TEXT("... There's no other way"))); // 1

			// 시작 대사
			playerStartScript.Emplace(FString::Printf(TEXT("Open the door and move to Bar Old Pal."))); // 0
			playerStartScript.Emplace(FString::Printf(TEXT("This is Old... Pal..."))); // 1
			playerStartScript.Emplace(FString::Printf(TEXT("Let's open the door and go down."))); // 2
			playerStartScript.Emplace(FString::Printf(TEXT("Let's open the door and go down."))); // 3
		}
	}
}
