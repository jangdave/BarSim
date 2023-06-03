// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerOrderWidget.h"
#include "Components/Image.h"

void UCustomerOrderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	// 여성 A
	// 주문
	womanScriptA.Emplace(FString::Printf(TEXT("진라임되죠? 한 잔 주세요"))); // 0
	womanScriptA.Emplace(FString::Printf(TEXT("다이키리되죠? 한 잔 주세요"))); // 1
	womanScriptA.Emplace(FString::Printf(TEXT("마티니되죠? 한 잔 주세요"))); // 2
	womanScriptA.Emplace(FString::Printf(TEXT("네그로니되죠? 한 잔 주세요"))); // 3
	// 한번
	womanScriptA.Emplace(FString::Printf(TEXT("이거 말고 진라임 주문했어요"))); // 4
	womanScriptA.Emplace(FString::Printf(TEXT("이거 말고 다이키리 주문했어요"))); // 5
	womanScriptA.Emplace(FString::Printf(TEXT("이거 말고 마티니 주문했어요"))); // 6
	womanScriptA.Emplace(FString::Printf(TEXT("이거 말고 네그로니 주문했어요"))); // 7
	// 두번
	womanScriptA.Emplace(FString::Printf(TEXT("주문한 메뉴도 제대로 못 만드시네요?"))); // 8
	womanScriptA.Emplace(FString::Printf(TEXT("맛있어요~ 딱이네요!"))); // 9
	womanScriptA.Emplace(FString::Printf(TEXT("음~ 뭔가 이상한데요"))); // 10
	
	// 여성 B
	// 주문
	womanScriptB.Emplace(FString::Printf(TEXT("진라임 한 잔 부탁해요"))); // 0
	womanScriptB.Emplace(FString::Printf(TEXT("다이키리 한 잔 부탁해요"))); // 1
	womanScriptB.Emplace(FString::Printf(TEXT("마티니 한 잔 부탁해요"))); // 2
	womanScriptB.Emplace(FString::Printf(TEXT("네그로니 한 잔 부탁해요"))); // 3
	// 한번
	womanScriptB.Emplace(FString::Printf(TEXT("진라임 맞아요?"))); // 4
	womanScriptB.Emplace(FString::Printf(TEXT("다이키리 맞아요?"))); // 5
	womanScriptB.Emplace(FString::Printf(TEXT("마티니 맞아요?"))); // 6
	womanScriptB.Emplace(FString::Printf(TEXT("네그로니 맞아요?"))); // 7
	// 두번
	womanScriptB.Emplace(FString::Printf(TEXT("서비스가 너무 하군요"))); // 8
	womanScriptB.Emplace(FString::Printf(TEXT("흠 잡을 데 없네요"))); // 9
	womanScriptB.Emplace(FString::Printf(TEXT("이건 좀 아쉽네요"))); // 10

	// 여성 C
	// 주문
	womanScriptC.Emplace(FString::Printf(TEXT("진라임."))); // 0
	womanScriptC.Emplace(FString::Printf(TEXT("다이키리."))); // 1
	womanScriptC.Emplace(FString::Printf(TEXT("마티니."))); // 2
	womanScriptC.Emplace(FString::Printf(TEXT("네그로니."))); // 3
	// 한번
	womanScriptC.Emplace(FString::Printf(TEXT("진라임 달라니까?"))); // 4
	womanScriptC.Emplace(FString::Printf(TEXT("다이키리 달라니까?"))); // 5
	womanScriptC.Emplace(FString::Printf(TEXT("마티니 달라니까?"))); // 6
	womanScriptC.Emplace(FString::Printf(TEXT("네그로니 달라니까?"))); // 7
	// 두번
	womanScriptC.Emplace(FString::Printf(TEXT("다신 오나봐라"))); // 8
	womanScriptC.Emplace(FString::Printf(TEXT("이 정도면 마실만 하네"))); // 9
	womanScriptC.Emplace(FString::Printf(TEXT("웩 이게 무슨 맛이야"))); // 10

	// 여성 D
	// 주문
	womanScriptD.Emplace(FString::Printf(TEXT("진라임...주세요"))); // 0
	womanScriptD.Emplace(FString::Printf(TEXT("다이키리...주세요"))); // 1
	womanScriptD.Emplace(FString::Printf(TEXT("마티니...주세요"))); // 2
	womanScriptD.Emplace(FString::Printf(TEXT("네그로니...주세요"))); // 3
	// 한번
	womanScriptD.Emplace(FString::Printf(TEXT("진라임 아닌거 같아요..."))); // 4
	womanScriptD.Emplace(FString::Printf(TEXT("다이키리 아닌거 같아요..."))); // 5
	womanScriptD.Emplace(FString::Printf(TEXT("마티니 아닌거 같아요..."))); // 6
	womanScriptD.Emplace(FString::Printf(TEXT("네그로니 아닌거 같아요..."))); // 7
	// 두번
	womanScriptD.Emplace(FString::Printf(TEXT("다음에 올게요..."))); // 8
	womanScriptD.Emplace(FString::Printf(TEXT("감사합니다..."))); // 9
	womanScriptD.Emplace(FString::Printf(TEXT("음...좀 이상하네요"))); // 10

	// 남성 A
	// 주문
	manScriptA.Emplace(FString::Printf(TEXT("진라임 주세요"))); // 0
	manScriptA.Emplace(FString::Printf(TEXT("다이키리 주세요"))); // 1
	manScriptA.Emplace(FString::Printf(TEXT("마티니 주세요"))); // 2
	manScriptA.Emplace(FString::Printf(TEXT("네그로니 주세요"))); // 3
	// 한번
	manScriptA.Emplace(FString::Printf(TEXT("주문한 진라임이 아닌거 같은데요?"))); // 4
	manScriptA.Emplace(FString::Printf(TEXT("주문한 다이키리가 아닌거 같은데요?"))); // 5
	manScriptA.Emplace(FString::Printf(TEXT("주문한 마티니가 아닌거 같은데요?"))); // 6
	manScriptA.Emplace(FString::Printf(TEXT("주문한 네그로니가 아닌거 같은데요?"))); // 7
	// 두번
	manScriptA.Emplace(FString::Printf(TEXT("주문한 메뉴를 안주다니 못참겠네요"))); // 8
	manScriptA.Emplace(FString::Printf(TEXT("맛있네요 잘 마셨습니다"))); // 9
	manScriptA.Emplace(FString::Printf(TEXT("음...제가 알던 맛이 아니네요"))); // 10
	
	// 남성 B
	// 주문
	manScriptB.Emplace(FString::Printf(TEXT("진라임 한 잔 부탁합니다"))); // 0
	manScriptB.Emplace(FString::Printf(TEXT("다이키리 한 잔 부탁합니다"))); // 1
	manScriptB.Emplace(FString::Printf(TEXT("마티니 한 잔 부탁합니다"))); // 2
	manScriptB.Emplace(FString::Printf(TEXT("네그로니 한 잔 부탁합니다"))); // 3
	// 한번
	manScriptB.Emplace(FString::Printf(TEXT("제가 시킨 진라임이 아닙니다"))); // 4
	manScriptB.Emplace(FString::Printf(TEXT("제가 시킨 다이키리가 아닙니다"))); // 5
	manScriptB.Emplace(FString::Printf(TEXT("제가 시킨 마티니가 아닙니다"))); // 6
	manScriptB.Emplace(FString::Printf(TEXT("제가 시킨 네그로니가 아닙니다"))); // 7
	// 두번
	manScriptB.Emplace(FString::Printf(TEXT("정말 형편 없군요 전 가겠습니다"))); // 8
	manScriptB.Emplace(FString::Printf(TEXT("맛이 잘 잡혀있군요 좋습니다"))); // 9
	manScriptB.Emplace(FString::Printf(TEXT("흠...밸런스가 안 맞는군요"))); // 10

	// 남성 C
	// 주문
	manScriptC.Emplace(FString::Printf(TEXT("바텐더 진라임 한잔"))); // 0
	manScriptC.Emplace(FString::Printf(TEXT("바텐더 다이키리 한잔"))); // 1
	manScriptC.Emplace(FString::Printf(TEXT("바텐더 마티니 한잔"))); // 2
	manScriptC.Emplace(FString::Printf(TEXT("바텐더 네그로니 한잔"))); // 3
	// 한번
	manScriptC.Emplace(FString::Printf(TEXT("진라임 시킨적 없는데?"))); // 4
	manScriptC.Emplace(FString::Printf(TEXT("다이키리 시킨적 없는데?"))); // 5
	manScriptC.Emplace(FString::Printf(TEXT("마티니 시킨적 없는데?"))); // 6
	manScriptC.Emplace(FString::Printf(TEXT("네그로니 시킨적 없는데?"))); // 7
	// 두번
	manScriptC.Emplace(FString::Printf(TEXT("뭐 이런 바가 있어? 나 참"))); // 8
	manScriptC.Emplace(FString::Printf(TEXT("이 정도면 못 마실 정도는 아니군"))); // 9
	manScriptC.Emplace(FString::Printf(TEXT("에잇 이것도 칵테일이라고 만든거야?"))); // 10

	// 남성 D
	// 주문
	manScriptD.Emplace(FString::Printf(TEXT("진라임 가능할까요...?"))); // 0
	manScriptD.Emplace(FString::Printf(TEXT("다이키리 가능할까요...?"))); // 1
	manScriptD.Emplace(FString::Printf(TEXT("마티니 가능할까요...?"))); // 2
	manScriptD.Emplace(FString::Printf(TEXT("네그로니 가능할까요...?"))); // 3
	// 한번
	manScriptD.Emplace(FString::Printf(TEXT("진라임 맞나요...?"))); // 4
	manScriptD.Emplace(FString::Printf(TEXT("다이키리 맞나요...?"))); // 5
	manScriptD.Emplace(FString::Printf(TEXT("마티니 맞나요...?"))); // 6
	manScriptD.Emplace(FString::Printf(TEXT("네그로니 맞나요...?"))); // 7
	// 두번
	manScriptD.Emplace(FString::Printf(TEXT("음...좀 실망스럽네요"))); // 8
	manScriptD.Emplace(FString::Printf(TEXT("맛있네요..."))); // 9
	manScriptD.Emplace(FString::Printf(TEXT("음...맛이 좀 이상하네요"))); // 10
}

void UCustomerOrderWidget::SetImage(UTexture2D* setTexture)
{
	image_Icon->SetBrushFromTexture(setTexture);
}

void UCustomerOrderWidget::SetOrderText()
{
	
}
