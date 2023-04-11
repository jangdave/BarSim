// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void TryGrabLeft();
	void TryGrabRight();
	void UnTryGrabLeft();
	void UnTryGrabRight();
	void Grabbing();

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float XMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float YMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class UMotionControllerComponent* LeftHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class UMotionControllerComponent* RightHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class USkeletalMeshComponent* LeftHandMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController")
	class USkeletalMeshComponent* RightHandMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HandComp", meta = (AllowPrivateAccess = true))
	class UMotionControllerComponent* RightAim;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Hand;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	float GrabRange = 150;

	UPROPERTY()
	class UPrimitiveComponent* GrabbedObject;

	// 잡은 녀석이 있는지 여부 기억할 변수
	bool IsGrabbedLeft = false;
	bool IsGrabbedRight = false;


	// 던지면 원하는 방향으로 날아가도록 하고싶다.
	// 던질 방향
	FVector ThrowDirection;
	// 던질 힘
	UPROPERTY(EditAnywhere, Category="Grab")
	float ThrowPower = 1000;
	// 직전 위치
	FVector PrevPos;
	// 이전 회전값
	FQuat PrevRot;
	// 회전방향
	FQuat DeltaRotation;
	// 회전빠르기
	UPROPERTY(EditAnywhere, Category="Grab")
	float ToquePower = 100;

};
