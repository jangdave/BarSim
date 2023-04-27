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
	void FireLeft();
	void FireReleased();
	void FireReleasedLeft();
	UFUNCTION()
	void TongsMovementExec();
	UFUNCTION()
	void TongsReleaseMovementExec();
	UFUNCTION()
	float GetDoorAngle();
	UFUNCTION()
	float GetDoorAngleLeft();
	
	

	// Tongs Movement Bool
	bool IsTongsMovementFinished = true;
	bool IsTongsReleaseMovementFinished = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
	class UInputAction* IA_FireLeft;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HandComp")
	class UMotionControllerComponent* LeftAim;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Hand;
	//UPROPERTY(EditDefaultsOnly, Category="Input")
	//class USphereComponent* tabletIndexComp;
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UWidgetInteractionComponent* widgetInteractionComp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	float GrabRange = 45;
	UPROPERTY(EditDefaultsOnly)
	float TongsGrabRange = 15;
	// 오른손 그랩 액터
	UPROPERTY()
	class AActor* GrabbedActorRight;
	// 왼손 그랩 액터
	UPROPERTY()
	class AActor* GrabbedActorLeft;
	// 오른손 그랩 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectRight;
	// 왼손 그랩 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectLeft;
	// Tongs를 통한 그랩 오른쪽 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectWithTongsRight;
	// Tongs를 통한 그랩 왼쪽 컴포넌트
	UPROPERTY()
	class UPrimitiveComponent* GrabbedObjectWithTongsLeft;
	// HuchuTong Ref
	UPROPERTY()
	class AHuchuTong* huchuTong;
	// HuchuTong Ref Left
	UPROPERTY()
	class AHuchuTong* huchuTongL;
	UPROPERTY()
	class ABottleBase* bottle;
	UPROPERTY()
	class ABottleBase* bottleL;
	UPROPERTY()
	class ATablet* tablet;
	UPROPERTY()
	class ATablet* tabletL;
	UPROPERTY()
	class ABarFridge* barFridge;
	UPROPERTY()
	class ABarFridge* barFridgeL;
	UPROPERTY()
	class AOpener* opener;
	UPROPERTY()
	class AOpener* openerL;
	UPROPERTY()
	class ACoaster* coaster;
	UPROPERTY()
	class ACoaster* coasterL;
	
	
	
	bool IsGrabbedLeft = false;
	bool IsGrabbedRight = false;
	bool isGrabbingTongsLeft = false;
	bool isGrabbingTongsRight = false;
	bool isGrabbingWithTongsRight=false;
	bool isGrabbingWithTongsLeft=false;
	bool isTongsTickEnabled = true;
	bool isTongsTickEnabledL = true;
	bool isRecipeMode = false;
	bool isGrabbingBottleRight = false;
	bool isGrabbingBottleLeft = false;
	bool isGrabbingFridgeDoorRight=false;
	bool isGrabbingFridgeDoorLeft=false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isGrabbingTabletRight = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isGrabbingTabletLeft = false;
	bool isGrabbingOpenerRight = false;
	bool isGrabbingOpenerLeft = false;
	bool isGrabbingCoasterRight=false;
	bool isGrabbingCoasterLeft = false;
	


	
	// 던질 방향
	FVector ThrowDirection;
	// 던질 방향
	FVector ThrowDirectionLeft;
	// 던질 힘
	UPROPERTY(EditAnywhere, Category="Grab")
	float ThrowPower = 150;
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
	// 회전방향 왼쪽
	FQuat DeltaRotationLeft;
	// 회전빠르기
	UPROPERTY(EditAnywhere, Category="Grab")
	float ToquePower = 3;
	// Grab한 대상의 크기
	UPROPERTY()
	double grabbingObjectSize = 0;
	// 왼쪽 Grab한 대상의 크기
	UPROPERTY()
	double grabbingObjectSizeL = 0;
	// index Finger Input value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	double fingerPressedActionValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input)
	double fingerPressedActionValueLeft;

};
