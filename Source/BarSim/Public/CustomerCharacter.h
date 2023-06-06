// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomerCharacter.generated.h"

UCLASS()
class BARSIM_API ACustomerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FSM)
	class UCustomerFSM* customerFSM;

	UPROPERTY(EditAnywhere)
	class UCustomerAnimInstance* customerAnim;

	// 주문시 나타날 위젯 컴포넌트
	UPROPERTY(EditAnywhere, Category=Widget)
	class UWidgetComponent* orderWidget;

	// 위젯 컴포넌트에 할당될 위젯
	UPROPERTY()
	class UCustomerOrderWidget* order_UI;

	UPROPERTY()
	class ACupBase* cup;

	UPROPERTY(EditAnywhere)
	class USoundBase* cashSound;
	
	// 스폰시 메쉬 설정 함수
	void SetMesh();

	// 남성 메쉬
	TArray<ConstructorHelpers::FObjectFinder<USkeletalMesh>> manMesh;

	// 여성 메쉬
	TArray<ConstructorHelpers::FObjectFinder<USkeletalMesh>> womenMesh;

	// 남성 여성 구별 변수
	UPROPERTY()
	int32 voiceCount;
	
	// 캐릭터 컵 오버랩 바인드 함수
	UFUNCTION()
	void BindOverlap();

	UFUNCTION()
	void DetachCup();
};
