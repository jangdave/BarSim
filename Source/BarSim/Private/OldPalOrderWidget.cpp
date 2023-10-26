// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalOrderWidget.h"

#include "BarGameInstance.h"
#include "Components/TextBlock.h"

void UOldPalOrderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	gi = Cast<UBarGameInstance>(GetGameInstance());
	
	SetLanguage();
}

void UOldPalOrderWidget::SetOldPalText(int32 idx)
{
	if(gi->checkDayCount == 1)
	{
		text_oldpal->SetText(FText::FromString(oldpalScript1[idx]));
	}
	else
	{
		text_oldpal->SetText(FText::FromString(oldpalScript3[idx]));
	}
}

void UOldPalOrderWidget::SetOldPalRecipe()
{
	text_oldpal->SetText(FText::FromString(oldpalScript3[10]));
	text_oldpal1->SetText(FText::FromString(oldpalScript3[9]));
	text_oldpal2->SetText(FText::FromString(oldpalScript3[8]));
}

void UOldPalOrderWidget::SetLanguage()
{
	if(gi)
	{
		// Language Setting = Korean
		if(gi->bEnglish==false)
		{
			// 첫째날 대화
			oldpalScript1.Emplace(FString::Printf(TEXT("그러지 말고, 단골인데 한 잔 만들어 주지 그래?"))); // 0
			//---------------------------------------------------------------------------선택
			// 나오고 선택지
			oldpalScript1.Emplace(FString::Printf(TEXT("아무 칵테일이나 좋으니, 자신있는 거로 하나 만들어 주게나"))); // 1
			// 혼잣말
			oldpalScript1.Emplace(FString::Printf(TEXT("이제는 여기 계단 내려오는 것도 힘이 드는군.."))); // 2
			oldpalScript1.Emplace(FString::Printf(TEXT("그래도 역시 뭘 마실 땐, 여기 올드팔이 제일 편해"))); // 3
			oldpalScript1.Emplace(FString::Printf(TEXT("새삼 이곳도 정말 오래된 친구 같아졌군 그래... 허허"))); // 4
			// 웨이팅
			oldpalScript1.Emplace(FString::Printf(TEXT("코스터가 없군."))); // 5
			oldpalScript1.Emplace(FString::Printf(TEXT("생각보다 오래 걸리는군."))); // 6
			//---------------------------------------------------------------------------선택
			oldpalScript1.Emplace(FString::Printf(TEXT("진라임인가..."))); // 7
			oldpalScript1.Emplace(FString::Printf(TEXT("다이키리인가..."))); // 8
			oldpalScript1.Emplace(FString::Printf(TEXT("마티니인가..."))); // 9
			oldpalScript1.Emplace(FString::Printf(TEXT("네그로니인가..."))); // 10
			oldpalScript1.Emplace(FString::Printf(TEXT("도무지 무슨 칵테일인지 알 수가 없군..."))); // 11
			//---------------------------------------------------------------------------
			oldpalScript1.Emplace(FString::Printf(TEXT("조금 덜 성숙한 맛이 나긴 하지만, 나쁘지 않군"))); // 12
			//---------------------------------------------------------------------------선택
			oldpalScript1.Emplace(FString::Printf(TEXT("다음 번에는 비율에 더 신경써서 만들면 더할 나위 없겠군"))); // 13
			oldpalScript1.Emplace(FString::Printf(TEXT("다음 번에는 양에 더 신경써서 만들면 더할 나위 없겠군"))); // 14
			oldpalScript1.Emplace(FString::Printf(TEXT("다음 번에는 기법에 더 신경써서 만들면 더할 나위 없겠군"))); // 15
			oldpalScript1.Emplace(FString::Printf(TEXT("기대 이상으로 훌륭하군"))); // 16
			oldpalScript1.Emplace(FString::Printf(TEXT("어떤 칵테일인지는 모르겠지만, 잘 마셨네"))); // 17
			//---------------------------------------------------------------------------
			oldpalScript1.Emplace(FString::Printf(TEXT("오늘은 한 잔 마셨으니 이만 돌아가보겠네"))); // 18
			oldpalScript1.Emplace(FString::Printf(TEXT("또 보세, 젊은 바텐더 선생"))); // 19

			// 셋째날 대화
			oldpalScript3.Emplace(FString::Printf(TEXT("오랜만이네, 젊은 바텐더 선생!"))); // 0
			oldpalScript3.Emplace(FString::Printf(TEXT("오랜만이라기엔, 이틀밖에 안됐지만 그래... 허허"))); // 1
			oldpalScript3.Emplace(FString::Printf(TEXT("오늘은 꼭 마시고 싶은 칵테일이 있어서"))); // 2
			oldpalScript3.Emplace(FString::Printf(TEXT("한번만 더 부탁하겠네"))); // 3
			oldpalScript3.Emplace(FString::Printf(TEXT("자네, 올드팔이라는 칵테일을 만들 줄 아나?"))); // 4
			oldpalScript3.Emplace(FString::Printf(TEXT("그러지 말고... 젊은 바텐더 선생"))); // 5
			oldpalScript3.Emplace(FString::Printf(TEXT("내가 레시피를 말해줄 테니, 만들어 보는게 어떤가?"))); // 6
			oldpalScript3.Emplace(FString::Printf(TEXT("하하, 좋네. 그럼 잘 듣고 만들어 보게나"))); // 7
			oldpalScript3.Emplace(FString::Printf(TEXT("우선 믹싱 글라스에 얼음을 담고 라이 위스키를 1온스"))); // 8
			oldpalScript3.Emplace(FString::Printf(TEXT("드라이 베르무트와 캄파리를 1온스씩 넣어주게나"))); // 9
			oldpalScript3.Emplace(FString::Printf(TEXT("다 넣었다면 10번정도 스터해주고, 마티니 글라스에 담아주면 끝이네"))); // 10
			oldpalScript3.Emplace(FString::Printf(TEXT("어디 한번 마셔보겠네"))); // 11
			oldpalScript3.Emplace(FString::Printf(TEXT("내가 말해준대로 잘 만들었나? 다시 만들어보게나"))); // 12
			oldpalScript3.Emplace(FString::Printf(TEXT("엉뚱한 칵테일을 만들었구만! 다시 만들어보게나"))); // 13
			oldpalScript3.Emplace(FString::Printf(TEXT("이게 바로 올드팔이야! 잘 기억해두라고, 바텐더 선생"))); // 14
			oldpalScript3.Emplace(FString::Printf(TEXT("조지가 만들던 맛이랑 정말 비슷해"))); // 15
			oldpalScript3.Emplace(FString::Printf(TEXT("그럼 물론이지, 허허"))); // 16
			oldpalScript3.Emplace(FString::Printf(TEXT("조지가 이 올드팔을 시작한게 벌써 30년도 더 됐군 그래"))); // 17
			oldpalScript3.Emplace(FString::Printf(TEXT("그러고보니 내 소개가 늦었군, 미안하네"))); // 18
			oldpalScript3.Emplace(FString::Printf(TEXT("젊은 바텐더 선생...아니 브랜든"))); // 19
			oldpalScript3.Emplace(FString::Printf(TEXT("내 이름은 리차드일세"))); // 20
			oldpalScript3.Emplace(FString::Printf(TEXT("맞네... 자넬 속일 생각은 없었는데"))); // 21
			oldpalScript3.Emplace(FString::Printf(TEXT("단골이자 자네 아버지의 친구로서, 테스트를 해보고 싶은 마음에 그만..."))); // 22
			oldpalScript3.Emplace(FString::Printf(TEXT("불쾌했다면 내가 사과하지"))); // 23
			oldpalScript3.Emplace(FString::Printf(TEXT("그러지 말고, 나랑 내기 하나 하는게 어떤가? 브랜든"))); // 24
			oldpalScript3.Emplace(FString::Printf(TEXT("사실 이 곳은 아버지가 자네에게 물려준다고 했지만, 전부는 아닐세"))); // 25
			oldpalScript3.Emplace(FString::Printf(TEXT("명의의 반은 내 앞으로 되어있네, 허허"))); // 26
			oldpalScript3.Emplace(FString::Printf(TEXT("어려운 걸 부탁하진 않겠네..."))); // 27
			oldpalScript3.Emplace(FString::Printf(TEXT("지금부터 딱 3달간 매주 일요일 찾아오겠네"))); // 28
			oldpalScript3.Emplace(FString::Printf(TEXT("자네는 매주 한잔씩, 내가 부탁하는 칵테일 총 12가지를"))); // 29
			oldpalScript3.Emplace(FString::Printf(TEXT("찾아서 나에게 완벽하게 만들어 주는거지"))); // 30
			oldpalScript3.Emplace(FString::Printf(TEXT("매주 테스트를 통과하면 다음 힌트를 주겠네"))); // 31
			oldpalScript3.Emplace(FString::Printf(TEXT("검색도 좋고, 이 바에 찾아오는 손님들과 대화해보면 알 수 있을걸세"))); // 32
			oldpalScript3.Emplace(FString::Printf(TEXT("물론 처음부터 어려운 칵테일을 요구하지는 않겠네. 허허"))); // 33
			oldpalScript3.Emplace(FString::Printf(TEXT("자네가 12가지의 칵테일을 완벽하게 만들어낸다면"))); // 34
			oldpalScript3.Emplace(FString::Printf(TEXT("내가 가진 이 올드팔의 지분을 자네에게 양도해주겠네"))); // 35
			oldpalScript3.Emplace(FString::Printf(TEXT("그땐 이 오래된 바를... 자네 마음대로 해도 좋네"))); // 36
			oldpalScript3.Emplace(FString::Printf(TEXT("그럴 줄 알았네! 허허"))); // 37
			oldpalScript3.Emplace(FString::Printf(TEXT("참고로 오늘 자네가 만든 올드팔은 말이지"))); // 38
			oldpalScript3.Emplace(FString::Printf(TEXT("알다시피 이 바의 이름이지"))); // 39
			oldpalScript3.Emplace(FString::Printf(TEXT("그건 자네 아버지 조지와 내가 젊었을 때 고른 이름이라네"))); // 40
			oldpalScript3.Emplace(FString::Printf(TEXT("그리고...나이 먹었을 때 쯤이면 오랜 친구같은 사이가 되었을"))); // 41
			oldpalScript3.Emplace(FString::Printf(TEXT("자신의 아들을 생각하면서 지은 이름이기도 하네"))); // 42
			oldpalScript3.Emplace(FString::Printf(TEXT("물론 자네가 조지를 어떻게 생각하는지 알고 있네"))); // 43
			oldpalScript3.Emplace(FString::Printf(TEXT("하지만, 그게 전부는 아닐지도 모르네"))); // 44
			oldpalScript3.Emplace(FString::Printf(TEXT("조지가 생각하고 느꼈던 것들을 한번 되돌아보는 것도, 도움이 될지 몰라"))); // 45
			oldpalScript3.Emplace(FString::Printf(TEXT("물론, 자네 자유일세"))); // 46
			oldpalScript3.Emplace(FString::Printf(TEXT("난 그저 오랜 친구와의 약속을 다할 뿐이니"))); // 47
			oldpalScript3.Emplace(FString::Printf(TEXT("어쨌든, 오늘 이야기는 여기까지 하지"))); // 48
			oldpalScript3.Emplace(FString::Printf(TEXT("다음 테스트를 통과하면, 조지 이야기를 하나씩 해주겠네"))); // 49
			oldpalScript3.Emplace(FString::Printf(TEXT("물론 자네가 원한다면 말이지, 하하"))); // 50
			oldpalScript3.Emplace(FString::Printf(TEXT("다음 주에 내가 자네에게 부탁할 칵테일은"))); // 51
			oldpalScript3.Emplace(FString::Printf(TEXT("젓지 말고, 흔들어서 만들어주게나, 쉽지?"))); // 52
			oldpalScript3.Emplace(FString::Printf(TEXT("다음 주에 또 오겠네, 브랜든"))); // 53
		}
		// Language Setting = English
		else
		{
			// 첫째날 대화
			oldpalScript1.Emplace(FString::Printf(TEXT("Ohhh... Don't do that. I'm a regular."))); // 0
			//---------------------------------------------------------------------------선택
			// 나오고 선택지
			oldpalScript1.Emplace(FString::Printf(TEXT("Any cocktail is fine... so make one of your own."))); // 1
			// 혼잣말
			oldpalScript1.Emplace(FString::Printf(TEXT("Now it's hard to even come down the stairs here."))); // 2
			oldpalScript1.Emplace(FString::Printf(TEXT("But, Old Pal is still the most comfortable place to drink."))); // 3
			oldpalScript1.Emplace(FString::Printf(TEXT("All over again, this place has become like an Old Pal. Yeah.."))); // 4
			// 웨이팅
			oldpalScript1.Emplace(FString::Printf(TEXT("There's no coaster..."))); // 5
			oldpalScript1.Emplace(FString::Printf(TEXT("It's taking longer than I thought..."))); // 6
			//---------------------------------------------------------------------------선택
			oldpalScript1.Emplace(FString::Printf(TEXT("It looks like gin lime..."))); // 7
			oldpalScript1.Emplace(FString::Printf(TEXT("It looks like... daiquiri..."))); // 8
			oldpalScript1.Emplace(FString::Printf(TEXT("Martini, I guess..."))); // 9
			oldpalScript1.Emplace(FString::Printf(TEXT("It seems like... Negroni...?"))); // 10
			oldpalScript1.Emplace(FString::Printf(TEXT("I can't guess what it is..."))); // 11
			//---------------------------------------------------------------------------
			oldpalScript1.Emplace(FString::Printf(TEXT("It tastes a little less mature, but... it's not that bad?"))); // 12
			//---------------------------------------------------------------------------선택
			oldpalScript1.Emplace(FString::Printf(TEXT("Next time, if you make it with a little more care, it will be perfect."))); // 13
			oldpalScript1.Emplace(FString::Printf(TEXT("Next time, if you make it with a little more care, it will be perfect."))); // 14
			oldpalScript1.Emplace(FString::Printf(TEXT("Next time, if you make it with a little more care, it will be perfect."))); // 15
			oldpalScript1.Emplace(FString::Printf(TEXT("It's better than I expected."))); // 16
			oldpalScript1.Emplace(FString::Printf(TEXT("I don't know what cocktail it is, but I enjoyed it."))); // 17
			//---------------------------------------------------------------------------
			oldpalScript1.Emplace(FString::Printf(TEXT("Today is the day, I drank one...... so...... i'm gonna go back today."))); // 18
			oldpalScript1.Emplace(FString::Printf(TEXT("See you again. Mr. Bartender."))); // 19

			// 셋째날 대화
			oldpalScript3.Emplace(FString::Printf(TEXT("Long time no see. Mr. Bartender."))); // 0
			oldpalScript3.Emplace(FString::Printf(TEXT("It's only been two days, but it is......"))); // 1
			oldpalScript3.Emplace(FString::Printf(TEXT("I won't ask you much. There's a cocktail I want to drink today."))); // 2
			oldpalScript3.Emplace(FString::Printf(TEXT("I'll ask you just one more time."))); // 3
			oldpalScript3.Emplace(FString::Printf(TEXT("Do you know how to make Old Pal?"))); // 4
			oldpalScript3.Emplace(FString::Printf(TEXT("Come on... Mr.Bartender."))); // 5
			oldpalScript3.Emplace(FString::Printf(TEXT("I'll tell you the recipe... so why don't you make me one?"))); // 6
			oldpalScript3.Emplace(FString::Printf(TEXT("Haha. That's good... Now, listen carefully and try it."))); // 7
			oldpalScript3.Emplace(FString::Printf(TEXT("First, put ice in the mixing glass and 1 ounce of Rye whisky..."))); // 8
			oldpalScript3.Emplace(FString::Printf(TEXT("then, add dry vermouth and campari 1 ounce each..."))); // 9
			oldpalScript3.Emplace(FString::Printf(TEXT("If you're done, stir it about 10 times and put it in a martini glass."))); // 10
			oldpalScript3.Emplace(FString::Printf(TEXT("Then... Let me try it."))); // 11
			oldpalScript3.Emplace(FString::Printf(TEXT("Did you make it like I told you? Try it again..."))); // 12
			oldpalScript3.Emplace(FString::Printf(TEXT("You made the wrong cocktail! Make it again."))); // 13
			oldpalScript3.Emplace(FString::Printf(TEXT("This is the Old Pal!! ... Remember, Mr. Bartender!"))); // 14
			oldpalScript3.Emplace(FString::Printf(TEXT("It tastes just like George's cocktail..."))); // 15
			oldpalScript3.Emplace(FString::Printf(TEXT("Of course... huh."))); // 16
			oldpalScript3.Emplace(FString::Printf(TEXT("It's already been more than 30 years since George started this bar."))); // 17
			oldpalScript3.Emplace(FString::Printf(TEXT("Come to think of it, I'm late to introduce myself ... I'm sorry."))); // 18
			oldpalScript3.Emplace(FString::Printf(TEXT("Mr.Bartender... No, Brandon..."))); // 19
			oldpalScript3.Emplace(FString::Printf(TEXT("My name is... Richard."))); // 20
			oldpalScript3.Emplace(FString::Printf(TEXT("Yeah... I didn't mean to trick you..."))); // 21
			oldpalScript3.Emplace(FString::Printf(TEXT("As a regular and a friend of your father's, ... I'd like to test it, so..."))); // 22
			oldpalScript3.Emplace(FString::Printf(TEXT("I apologize if it was unpleasant."))); // 23
			oldpalScript3.Emplace(FString::Printf(TEXT("Come on...Why don't you make a bet with me...? Brandon"))); // 24
			oldpalScript3.Emplace(FString::Printf(TEXT("In fact, your father said he'd hand this over to you..."))); // 25
			oldpalScript3.Emplace(FString::Printf(TEXT("Half of this bar is on me... haha."))); // 26
			oldpalScript3.Emplace(FString::Printf(TEXT("I won't ask you to do anything difficult..."))); // 27
			oldpalScript3.Emplace(FString::Printf(TEXT("I'll be back every Sunday for 3 months from now."))); // 28
			oldpalScript3.Emplace(FString::Printf(TEXT("You get a drink every week a total of 12 cocktails I ask for."))); // 29
			oldpalScript3.Emplace(FString::Printf(TEXT("Find it and make it perfect for me."))); // 30
			oldpalScript3.Emplace(FString::Printf(TEXT("If you pass the test every week. I'll give you the next hint."))); // 31
			oldpalScript3.Emplace(FString::Printf(TEXT("It's good to search. and if you talk to the customers who come to this bar"))); // 32
			oldpalScript3.Emplace(FString::Printf(TEXT("Of course, I won't ask for a difficult one... from the beginning."))); // 33
			oldpalScript3.Emplace(FString::Printf(TEXT("If you make 12 cocktails perfectly,"))); // 34
			oldpalScript3.Emplace(FString::Printf(TEXT("I'm gonna give you the half of Old Pal."))); // 35
			oldpalScript3.Emplace(FString::Printf(TEXT("When that time comes... this old bar, you can do as you want."))); // 36
			oldpalScript3.Emplace(FString::Printf(TEXT("I knew it! haha!"))); // 37
			oldpalScript3.Emplace(FString::Printf(TEXT("By the way...The Old Pal you made today..."))); // 38
			oldpalScript3.Emplace(FString::Printf(TEXT("As you know... It's the name of this bar."))); // 39
			oldpalScript3.Emplace(FString::Printf(TEXT("That's the name your father George and I chose... when we were young..."))); // 40
			oldpalScript3.Emplace(FString::Printf(TEXT("And...Also, It was named after... who would have been like an Old Pal..."))); // 41
			oldpalScript3.Emplace(FString::Printf(TEXT("It was named after...... the son."))); // 42
			oldpalScript3.Emplace(FString::Printf(TEXT("Of course... I know how you think of George."))); // 43
			oldpalScript3.Emplace(FString::Printf(TEXT("But... maybe that's not all..."))); // 44
			oldpalScript3.Emplace(FString::Printf(TEXT("It might be helpful to look back on... What George thought and felt."))); // 45
			oldpalScript3.Emplace(FString::Printf(TEXT("Of course, it's on you."))); // 46
			oldpalScript3.Emplace(FString::Printf(TEXT("I just keep my word with my Old Pal..."))); // 47
			oldpalScript3.Emplace(FString::Printf(TEXT("Anyway, that's it for today."))); // 48
			oldpalScript3.Emplace(FString::Printf(TEXT("If you pass the next test... I'll tell you about George one by one."))); // 49
			oldpalScript3.Emplace(FString::Printf(TEXT("Of course if you want...! HAHA!"))); // 50
			oldpalScript3.Emplace(FString::Printf(TEXT("The cocktail I'm gonna ask you for next week is..."))); // 51
			oldpalScript3.Emplace(FString::Printf(TEXT("Shaken, Not Stirred. ... Easy, huh?"))); // 52
			oldpalScript3.Emplace(FString::Printf(TEXT("Then, I'll be back next week... Brandon."))); // 53
		}
	}
}
