// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HuchuTong.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BarPlayer.generated.h"



UCLASS()
class BARSIM_API ABarPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABarPlayer();

	void Turn(const FInputActionValue& Values);
	void Move(const FInputActionValue& Values);
	void Jump();
	void JumpEnd();
	// 왼손 그랩
	void TryGrabLeft();
	// 오른손 그랩
	void TryGrabRight();
	// 왼손 그랩 해제
	void UnTryGrabLeft();
	// 오른손 그랩 해제
	void UnTryGrabRight();
	// 그랩한 대상 위치값 업데이트
	void Grabbing();
	void Fire();
	void FireReleased();
	UFUNCTION()
	void TongsMovementExec();
	UFUNCTION()
	void TongsReleaseMovementExec();

	// Tongs Movement Bool
	bool IsTongsMovementFinished = true;
	bool IsTongsReleaseMovementFinished = true;

	UPROPERTY(BlueprintReadOnly)
	class UCameraComponent* FPSCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float moveSpeed = 500.0f;
	// Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Default;
	// Input Action for Move
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Fire;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Grab_Left;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Grab_Right;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class UMotionControllerComponent* LeftHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class UMotionControllerComponent* RightHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class USkeletalMeshComponent* LeftHandMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class USkeletalMeshComponent* RightHandMesh;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HandComp")
	class UMotionControllerComponent* RightAim;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Hand;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float XMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float YMovement;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	float GrabRange = 100;
	// 오른손 그랩 액터
	UPROPERTY()
	class AActor* GrabbedActorRight;
	// 오른손 그랩 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectRight;
	// 왼손 그랩 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectLeft;
	UPROPERTY()
	class AHuchuTong* huchuTong;
	
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings")
	TSubclassOf<class ATongCollision> tongCol;
	


	// 잡은 대상이 있는지 여부 기억할 변수
	bool IsGrabbedLeft = false;
	bool IsGrabbedRight = false;
	bool isGrabbingTongsLeft = false;
	bool isGrabbingTongsRight = false;
	// 던질 방향
	FVector ThrowDirection;
	// 던질 힘
	UPROPERTY(EditAnywhere, Category="Grab")
	float ThrowPower = 100;
	// 오른 손 직전 위치
	FVector PrevPosRight;
	// 오른 손 이전 회전값
	FQuat PrevRotRight;
	// 왼손 직전 위치
	FVector PrevPosLeft;
	// 왼손 이전 회전값
	FQuat PrevRotLeft;
	// 회전방향
	FQuat DeltaRotation;
	// 회전빠르기
	UPROPERTY(EditAnywhere, Category="Grab")
	float ToquePower = 10;

};
