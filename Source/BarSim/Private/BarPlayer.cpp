// Fill out your copyright notice in the Description page of Project Settings.


#include "BarPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Chaos/ChaosPerfTest.h"


// Sets default values
ABarPlayer::ABarPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(RootComponent);
	LeftHand->SetTrackingMotionSource(FName("Left"));
	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));

	RightHand->SetupAttachment(RootComponent);
	RightHand->SetTrackingMotionSource(FName("Right"));

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(LeftHand);
	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightHand);

	RightAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightAim"));
	RightAim->SetupAttachment(RootComponent);
	RightAim->SetTrackingMotionSource(FName("RightAim"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_left.SKM_QuinnXR_left'"));
	if (TempMesh.Succeeded())
	{
		LeftHandMesh->SetSkeletalMesh(TempMesh.Object);
		LeftHandMesh->SetRelativeLocation(FVector(-2.9f, -3.5f, 4.5f));
		LeftHandMesh->SetRelativeRotation(FRotator(-25, -180, 90));
	}

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_right.SKM_QuinnXR_right'"));
	if (TempMesh2.Succeeded())
	{
		RightHandMesh->SetSkeletalMesh(TempMesh2.Object);
		RightHandMesh->SetRelativeLocation(FVector(-2.9f, 3.5f, 4.5f));
		RightHandMesh->SetRelativeRotation(FRotator(25, 0, 90));
	}

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	FPSCamera->SetupAttachment(RootComponent);
	FPSCamera->bUsePawnControlRotation = false;
	
}

// Called when the game starts or when spawned
void ABarPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input 
	auto PC = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		// LocalPlayer
		auto localPlayer = PC->GetLocalPlayer();
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (subSystem)
		{
			subSystem->AddMappingContext(IMC_Default, 0);
			subSystem->AddMappingContext(IMC_Hand, 0);
		}
	}

	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled() == false)
	{
		RightAim->SetRelativeLocation(FVector(20, 20, 0));
		RightHand->SetRelativeLocation(FVector(20, 20, 0));
		FPSCamera->bUsePawnControlRotation = true;

		FPSCamera->AddRelativeLocation(FVector(0, 0, 88));


	}
	else
	{
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
		FPSCamera->bUsePawnControlRotation = false;
	}


	
}

// Called every frame
void ABarPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled() == false)
	{
		RightHand->SetRelativeRotation(FPSCamera->GetRelativeRotation());
		RightAim->SetRelativeRotation(FPSCamera->GetRelativeRotation());
	}

	Grabbing();
	
}

// Called to bind functionality to input
void ABarPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto InputSystem = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputSystem)
	{
		//Binding
		InputSystem->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABarPlayer::Move);
		InputSystem->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABarPlayer::Turn);
		InputSystem->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ABarPlayer::Jump);
		InputSystem->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABarPlayer::JumpEnd);
		InputSystem->BindAction(IA_Grab_Left, ETriggerEvent::Started, this, &ABarPlayer::TryGrabLeft);
		InputSystem->BindAction(IA_Grab_Left, ETriggerEvent::Completed, this, &ABarPlayer::UnTryGrabLeft);
		InputSystem->BindAction(IA_Grab_Right, ETriggerEvent::Started, this, &ABarPlayer::TryGrabRight);
		InputSystem->BindAction(IA_Grab_Right, ETriggerEvent::Completed, this, &ABarPlayer::UnTryGrabRight);
		InputSystem->BindAction(IA_Fire, ETriggerEvent::Started, this, &ABarPlayer::Fire);
		InputSystem->BindAction(IA_Fire, ETriggerEvent::Completed, this, &ABarPlayer::FireReleased);
	}
	
}

void ABarPlayer::Move(const FInputActionValue& Values)
{
	FVector2D Axis = Values.Get<FVector2D>();
	XMovement = Axis.X;
	YMovement = Axis.Y;
	AddMovementInput(GetActorForwardVector(), Axis.Y);
	AddMovementInput(GetActorRightVector(), Axis.X);
}

void ABarPlayer::Turn(const FInputActionValue& Values)
{
	FVector2D Axis = Values.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void ABarPlayer::Jump()
{
	ACharacter::Jump();
}

void ABarPlayer::JumpEnd()
{
	ACharacter::StopJumping();
}

void ABarPlayer::Fire()
{
	if(isGrabbingTongsRight||isGrabbingTongsLeft)
	{
		/*FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget=this;
		UKismetSystemLibrary::MoveComponentTo();*/




		
	}

	
}

void ABarPlayer::FireReleased()
{
}


void ABarPlayer::TryGrabLeft()
{
	// 중심점
	FVector Center = LeftHand->GetComponentLocation();
	// 충돌체크(구충돌)
	//DrawDebugSphere(GetWorld(), Center, 100, 30, FColor::Red, false, 2.0f);
	// 충돌한 물체를 기억할 배열
	TArray<FOverlapResult> HitObj;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredComponent(LeftHand);
	bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(GrabRange), params);
	if (bHit == false)
	{
		return;
	}
	// 가장 가까운 물체를 잡도록 하자
	// 가장 가까운 물체 인덱스
	int32 Closest = 0;
	for (int i = 0; i < HitObj.Num(); ++i)
	{
		// 1. 물리기능이 활성화 되어 있는 대상만 판단
		if (HitObj[i].GetComponent()->IsSimulatingPhysics() == false)
		{
			continue;
		}
		// 잡기에 성공했다
		IsGrabbedLeft = true;
		// 2.. 현재 손과 가장 가까운 대상과 이번에 검출할 대상과 더 가까운 대상이 있다면		
		// 필요속성 : 현재 가장 가까운 대상과 손과의 거리
		float ClosestDist = FVector::Dist(HitObj[Closest].GetActor()->GetActorLocation(), Center);
		// 필요속성 : 이번에 검출할 대상과 손과의 거리
		float NextDist = FVector::Dist(HitObj[0].GetActor()->GetActorLocation(), Center);

		// 3. 만약 이번 대상이 현재 대상보다 가깝다면,
		if (NextDist < ClosestDist)
		{

			// 가장 가까운 대상으로 변경하기
			Closest = i;
		}
	}

	// 잡기에 성공했다면
	if (IsGrabbedLeft)
	{
		// 물체 물리기능 비활성화
		GrabbedObjectLeft = HitObj[Closest].GetComponent();
		GrabbedObjectLeft->SetSimulatePhysics(false);
		GrabbedObjectLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// 손에 붙여주자
		GrabbedObjectLeft->AttachToComponent(LeftHand, FAttachmentTransformRules::KeepWorldTransform);
	}

}

void ABarPlayer::TryGrabRight()
{
	// 중심점
	FVector Center = RightHand->GetComponentLocation();
	// 충돌체크(구충돌)
	//DrawDebugSphere(GetWorld(), Center, 100, 30, FColor::Red, false, 2.0f);
	// 충돌한 물체를 기억할 배열
	TArray<FOverlapResult> HitObj;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredComponent(RightHand);
	bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(GrabRange), params);
	if (bHit == false)
	{
		return;
	}
	// 가장 가까운 물체를 잡도록 하자
	// 가장 가까운 물체 인덱스
	int32 Closest = 0;
	for (int i = 0; i < HitObj.Num(); ++i)
	{
		// 1. 물리기능이 활성화 되어 있는 대상만 판단
		if (HitObj[i].GetComponent()->IsSimulatingPhysics() == false)
		{
			continue;
		}
		// 잡기에 성공했다
		IsGrabbedRight = true;
		// 2.. 현재 손과 가장 가까운 대상과 이번에 검출할 대상과 더 가까운 대상이 있다면		
		// 필요속성 : 현재 가장 가까운 대상과 손과의 거리
		float ClosestDist = FVector::Dist(HitObj[Closest].GetActor()->GetActorLocation(), Center);
		// 필요속성 : 이번에 검출할 대상과 손과의 거리
		float NextDist = FVector::Dist(HitObj[0].GetActor()->GetActorLocation(), Center);

		// 3. 만약 이번 대상이 현재 대상보다 가깝다면,
		if (NextDist < ClosestDist)
		{

			// 가장 가까운 대상으로 변경하기
			Closest = i;
		}
	}

	// 잡기에 성공했다면
	if (IsGrabbedRight)
	{
		// 물체 물리기능 비활성화
		GrabbedObjectRight = HitObj[Closest].GetComponent();
		GrabbedObjectRight->SetSimulatePhysics(false);
		//GrabbedObjectRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// 손에 붙여주자
		GrabbedObjectRight->AttachToComponent(RightHand, FAttachmentTransformRules::KeepWorldTransform);
		if(GrabbedObjectRight->GetName().Contains(TEXT("BP_HuchuTong")))
		{
			isGrabbingTongsRight=true;
			UE_LOG(LogTemp, Warning, TEXT("grab huchu"))
		}
	}

}
void ABarPlayer::UnTryGrabLeft()
{
	if (IsGrabbedLeft == false)
	{
		return;
	}

	// 1. 잡지않은 상태로 전환
	IsGrabbedLeft = false;
	// 2. 손에서 떼어내기
	GrabbedObjectLeft->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	// 3. 물리기능 활성화
	GrabbedObjectLeft->SetSimulatePhysics(true);
	// 4. 충돌기능 활성화
	GrabbedObjectLeft->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// 던지기
	GrabbedObjectLeft->AddForce(ThrowDirection * ThrowPower * GrabbedObjectLeft->GetMass());

	// 회전 시키기
	// 각속도 = (1 / dt) * dTheta(특정 축 기준 변위 각도 Axis, angle)
	float Angle;
	FVector Axis;
	DeltaRotation.ToAxisAndAngle(Axis, Angle);
	float dt = GetWorld()->DeltaTimeSeconds;
	FVector AngularVelocity = (1.0f / dt) * Angle * Axis;
	GrabbedObjectLeft->SetPhysicsAngularVelocityInRadians(AngularVelocity * ToquePower, true);

	GrabbedObjectLeft = nullptr;
}

void ABarPlayer::UnTryGrabRight()
{
	if (IsGrabbedRight == false)
	{
		return;
	}

	// 1. 잡지않은 상태로 전환
	IsGrabbedRight = false;
	// 2. 손에서 떼어내기
	GrabbedObjectRight->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	// 3. 물리기능 활성화
	GrabbedObjectRight->SetSimulatePhysics(true);
	// 4. 충돌기능 활성화
	GrabbedObjectRight->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// 던지기
	GrabbedObjectRight->AddForce(ThrowDirection * ThrowPower * GrabbedObjectRight->GetMass());

	// 회전 시키기
	// 각속도 = (1 / dt) * dTheta(특정 축 기준 변위 각도 Axis, angle)
	float Angle;
	FVector Axis;
	DeltaRotation.ToAxisAndAngle(Axis, Angle);
	float dt = GetWorld()->DeltaTimeSeconds;
	FVector AngularVelocity = (1.0f / dt) * Angle * Axis;
	GrabbedObjectRight->SetPhysicsAngularVelocityInRadians(AngularVelocity * ToquePower, true);

	GrabbedObjectRight = nullptr;
}

// 던질 정보를 업데이트하기위한 기능
void ABarPlayer::Grabbing()
{
	if (IsGrabbedLeft&&IsGrabbedRight == false)
	{
		return;
	}
if(IsGrabbedRight)
{
	// 던질방향 업데이트
	ThrowDirection = RightHand->GetComponentLocation() - PrevPosRight;
	// 회전방향 업데이트
	// 쿼터니온 공식
	DeltaRotation = RightHand->GetComponentQuat() * PrevRotRight.Inverse();

	// 이전위치 업데이트
	PrevPosRight = RightHand->GetComponentLocation();
	// 이전회전값 업데이트
	PrevRotRight = RightHand->GetComponentQuat();
}
	if(IsGrabbedLeft)
	{
		// 던질방향 업데이트
		ThrowDirection = RightHand->GetComponentLocation() - PrevPosLeft;
		// 회전방향 업데이트
		// 쿼터니온 공식
		DeltaRotation = RightHand->GetComponentQuat() * PrevRotLeft.Inverse();

		// 이전위치 업데이트
		PrevPosLeft = RightHand->GetComponentLocation();
		// 이전회전값 업데이트
		PrevRotLeft = RightHand->GetComponentQuat();
	}
}

