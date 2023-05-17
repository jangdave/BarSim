// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "BarSpoon.h"
#include "BottleBase.h"
#include "Coaster.h"
#include "CupBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GripMotionControllerComponent.h"
#include "HalfSlicedLime.h"
#include "HuchuTong.h"
#include "IceCube.h"
#include "MixingGlass.h"
#include "Shaker.h"
#include "ShakerLid.h"
#include "ShakerStrainer.h"
#include "SlicedLime.h"
#include "Strainer.h"
#include "Tablet.h"
#include "Components/WidgetInteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"


APlayerCharacter::APlayerCharacter()
{

	widgetInteractionComp = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("widgetInteractionComp"));
	widgetInteractionComp->SetupAttachment(RightMotionController);
	widgetInteractionComp->SetRelativeLocation(FVector(9.1321, -2.7411, -8.8955));
	widgetInteractionComp->SetRelativeRotation(FRotator(-59.678, -36.935, 52.896));

	widgetInteractionCompLeft = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("widgetInteractionCompLeft"));
	widgetInteractionCompLeft->SetupAttachment(LeftMotionController);
	widgetInteractionCompLeft->SetRelativeLocation(FVector(9.0641, 5.1962, -10.4361));
	widgetInteractionCompLeft->SetRelativeRotation(FRotator(-52.5329, 21.7898, -2.4338));
}


void APlayerCharacter::BeginPlay()
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
			subSystem->AddMappingContext(VREInputMappingContext, 0);
			subSystem->AddMappingContext(IMC_Hand, 0);
		}
	}

	GetCharacterMovement()->bRequestedMoveUseAcceleration=false;
	GetCharacterMovement()->bNetworkSkipProxyPredictionOnNetUpdate=true;
	LeftMotionController->bSmoothHandTracking=true;
	RightMotionController->bSmoothHandTracking=true;
	
	widgetInteractionComp->DebugSphereLineThickness=0;
	widgetInteractionComp->DebugLineThickness=0.3f;
	widgetInteractionComp->DebugColor=FColor::White;
	widgetInteractionComp->bEnableHitTesting=true;
	widgetInteractionComp->bShowDebug=false;	
	widgetInteractionComp->InteractionDistance=40.0f;

	widgetInteractionCompLeft->DebugSphereLineThickness=0;
	widgetInteractionCompLeft->DebugLineThickness=0.3f;
	widgetInteractionCompLeft->DebugColor=FColor::White;
	widgetInteractionCompLeft->bEnableHitTesting=true;
	widgetInteractionCompLeft->bShowDebug=false;	
	widgetInteractionCompLeft->InteractionDistance=40.0f;
	
}



void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tongs가 nullptr이 아니면서
	if(huchuTong!=nullptr)
	{
		// 오른손에 Tongs를 쥐고 있다면
		if(isGrabbingTongsRight)
		{
			// Oculus Trigger Input Value에 따른 Tongs Rotation 제어 Tick 활성화가 되어있다면
			if(isTongsTickEnabled == true)
			{
				huchuTong->tongRight->SetRelativeRotation(FRotator(fingerPressedActionValue*15, 0, 0));
			}
			
		}
	}
	// Tongs가 nullptr이 아니면서
	if(huchuTongL!=nullptr)
	{
		// 왼손에 Tongs를 쥐고 있다면
		if(isGrabbingTongsLeft)
		{
			// Oculus Trigger Input Value에 따른 Tongs Rotation 제어 Tick 왼쪽 활성화가 되어있다면
			if(isTongsTickEnabledL == true)
			{
				huchuTongL->tongRight->SetRelativeRotation(FRotator(fingerPressedActionValueLeft*15, 0, 0));
			}
			
		}
	}	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	auto InputSystem = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputSystem)
	{
		//Binding
		InputSystem->BindAction(UseHeldObjectLeft, ETriggerEvent::Started, this, &APlayerCharacter::FireLeft);
		InputSystem->BindAction(UseHeldObjectRight, ETriggerEvent::Started, this, &APlayerCharacter::FireRight);
		InputSystem->BindAction(UseHeldObjectLeft, ETriggerEvent::Completed, this, &APlayerCharacter::FireReleasedLeft);
		InputSystem->BindAction(UseHeldObjectRight, ETriggerEvent::Completed, this, &APlayerCharacter::FireReleasedRight);
	}
}

void APlayerCharacter::CheckGrabbedObjectRight()
{
	TArray<AActor*> RightGrippedActors;
	RightMotionController->GetGrippedActors(RightGrippedActors);
	for(int i=0; i<RightGrippedActors.Num(); ++i)
	{
		GrabbedActorRight = RightGrippedActors[i];
	}

	// Right Grabbed Actor Casting
	huchuTong=Cast<AHuchuTong>(GrabbedActorRight);
	bottle = Cast<ABottleBase>(GrabbedActorRight);
	tablet = Cast<ATablet>(GrabbedActorRight);
	coaster=Cast<ACoaster>(GrabbedActorRight);
	cup=Cast<ACupBase>(GrabbedActorRight);
	barSpoon=Cast<ABarSpoon>(GrabbedActorRight);
	strainer=Cast<AStrainer>(GrabbedActorRight);
	shakerStrainer=Cast<AShakerStrainer>(GrabbedActorRight);
	shakerLid=Cast<AShakerLid>(GrabbedActorRight);
	shaker=Cast<AShaker>(GrabbedActorRight);
	mixingGlass=Cast<AMixingGlass>(GrabbedActorRight);
	
		// 잡은 대상이 Tongs라면
		if(GrabbedActorRight==huchuTong&&huchuTong!=nullptr)
		{
		isGrabbingTongsRight=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed Huchu Right"));
		}
		// 잡은 대상이 Bottle 이라면
		else if(GrabbedActorRight == bottle&&bottle!=nullptr)
		{
			isGrabbingBottleRight = true;
			UE_LOG(LogTemp, Warning, TEXT("Grabbed bottle on Right"))
		}
		// 잡은 대상이 Tablet 이라면
		else if(GrabbedActorRight==tablet&&tablet!=nullptr)
		{
			isGrabbingTabletRight=true;
			widgetInteractionComp->bShowDebug=false;
			widgetInteractionCompLeft->bShowDebug=true;
			UE_LOG(LogTemp, Warning, TEXT("Grabbed tablet on Right"))
		}		
		// 잡은 대상이 Coaster이라면
		else if(GrabbedActorRight==coaster&&coaster!=nullptr)
		{
			isGrabbingCoasterRight=true;
			UE_LOG(LogTemp, Warning, TEXT("Grabbed coaster on Right"))			
		}
		// 잡은 대상이 Cup이라면
		else if(GrabbedActorRight==cup&&cup!=nullptr)
		{
			isGrabbingCupRight=true;
			cup->isCupTickActivated=true;
			UE_LOG(LogTemp, Warning, TEXT("Grabbed cup on Right"))			
		}
		// 잡은 대상이 BarSpoon이라면
		else if(GrabbedActorRight==barSpoon&&barSpoon!=nullptr)
		{
			isGrabbingBarSpoonRight=true;
			UE_LOG(LogTemp, Warning, TEXT("Grabbed barspoon on Right"))			
		}
		// 잡은 대상이 Shaker이라면
		else if(GrabbedActorRight==shaker&&shaker!=nullptr)
		{
		isGrabbingShakerRight=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed shaker on Right"))			
		}
		// 잡은 대상이 ShakerLid라면
		else if(GrabbedActorRight==shakerLid&&shakerLid!=nullptr)
		{
			isGrabbingShakerLidRight=true;
			shakerLid->VRGripInterfaceSettings.bSimulateOnDrop=true;
			shakerLid->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			UE_LOG(LogTemp, Warning, TEXT("Grabbed Shaker Lid on Right"))			
		}
		// 잡은 대상이 ShakerStrainer 이라면
		else if(GrabbedActorRight==shakerStrainer&&shakerStrainer!=nullptr)
		{
			isGrabbingShakerStrainerRight=true;
			shakerStrainer->VRGripInterfaceSettings.bSimulateOnDrop=true;
			shakerStrainer->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			UE_LOG(LogTemp, Warning, TEXT("Grabbed Shaker Strainer on Right"))			
		}
		// 잡은 대상이 MixingGlass 라면
		else if(GrabbedActorRight==mixingGlass&&mixingGlass!=nullptr)
		{
			isGrabbingMixingGlassRight=true;
			mixingGlass->VRGripInterfaceSettings.bSimulateOnDrop=true;
			UE_LOG(LogTemp, Warning, TEXT("Grabbed Mixing Glass  on Right"))			
		}
		// 잡은 대상이 Glass Strainer 이라면
		else if(GrabbedActorRight==strainer&&strainer!=nullptr)
		{
			isGrabbingStrainerRight=true;
			strainer->VRGripInterfaceSettings.bSimulateOnDrop=true;
			strainer->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			UE_LOG(LogTemp, Warning, TEXT("Grabbed Glass Strainer on Right"))			

		}
	
	
}

void APlayerCharacter::CheckGrabbedObjectLeft()
{
	TArray<AActor*> LeftGrippedActors;
	LeftMotionController->GetGrippedActors(LeftGrippedActors);
	for(int i=0; i<LeftGrippedActors.Num(); ++i)
	{
		GrabbedActorLeft = LeftGrippedActors[i];
	}

	// Left Grabbed Actor Casting
	huchuTongL=Cast<AHuchuTong>(GrabbedActorLeft);
	bottleL = Cast<ABottleBase>(GrabbedActorLeft);
	tabletL = Cast<ATablet>(GrabbedActorLeft);
	coasterL=Cast<ACoaster>(GrabbedActorLeft);
	cupL=Cast<ACupBase>(GrabbedActorLeft);
	barSpoonL=Cast<ABarSpoon>(GrabbedActorLeft);
	strainerL=Cast<AStrainer>(GrabbedActorLeft);
	shakerStrainerL=Cast<AShakerStrainer>(GrabbedActorLeft);
	shakerLidL=Cast<AShakerLid>(GrabbedActorLeft);
	shakerL=Cast<AShaker>(GrabbedActorLeft);
	mixingGlassL=Cast<AMixingGlass>(GrabbedActorLeft);
	
	// 잡은 대상이 Tongs라면
	if(GrabbedActorLeft==huchuTongL&&huchuTongL!=nullptr)
	{
		isGrabbingTongsLeft=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed Huchu Left"));
	}
	// 잡은 대상이 Bottle 이라면
	else if(GrabbedActorLeft == bottleL&&bottleL!=nullptr)
	{
		isGrabbingBottleLeft = true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed bottle on Left"))
	}
	// 잡은 대상이 Tablet 이라면
	else if(GrabbedActorLeft==tabletL&&tabletL!=nullptr)
	{
		isGrabbingTabletLeft=true;
		widgetInteractionComp->bShowDebug=true;
		widgetInteractionCompLeft->bShowDebug=false;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed tablet on Left"))
	}		
	// 잡은 대상이 Coaster이라면
	else if(GrabbedActorLeft==coasterL&&coasterL!=nullptr)
	{
		isGrabbingCoasterLeft=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed coaster on Left"))			
	}
	// 잡은 대상이 Cup이라면
	else if(GrabbedActorLeft==cupL&&cupL!=nullptr)
	{
		isGrabbingCupLeft=true;
		cupL->isCupTickActivated=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed cup on Left"))			
	}
	// 잡은 대상이 BarSpoon이라면
	else if(GrabbedActorLeft==barSpoonL&&barSpoonL!=nullptr)
	{
		isGrabbingBarSpoonLeft=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed barspoon on Left"))			
	}
	// 잡은 대상이 Shaker이라면
	else if(GrabbedActorLeft==shakerL&&shakerL!=nullptr)
	{
		isGrabbingShakerLeft=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed shaker on Left"))			
	}
	// 잡은 대상이 ShakerLid라면
	else if(GrabbedActorLeft==shakerLidL&&shakerLidL!=nullptr)
	{
		isGrabbingShakerLidLeft=true;
		shakerLidL->isLidAttachable=false;
		shakerLidL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Warning, TEXT("Grabbed Shaker Lid on Left"))			
	}
	// 잡은 대상이 ShakerStrainer 이라면
	else if(GrabbedActorLeft==shakerStrainerL&&shakerStrainerL!=nullptr)
	{
		isGrabbingShakerStrainerLeft=true;
		shakerStrainerL->isStrainerAttachable = false;
		shakerStrainerL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Warning, TEXT("Grabbed Shaker Strainer on Left"))			
	}
	// 잡은 대상이 MixingGlass 라면
	else if(GrabbedActorLeft==mixingGlassL&&mixingGlassL!=nullptr)
	{
		isGrabbingMixingGlassLeft=true;
		mixingGlassL->VRGripInterfaceSettings.bSimulateOnDrop=true;
		UE_LOG(LogTemp, Warning, TEXT("Grabbed Mixing Glass  on Left"))			
	}
	// 잡은 대상이 Glass Strainer 이라면
	else if(GrabbedActorLeft==strainerL&&strainerL!=nullptr)
	{
		isGrabbingStrainerLeft=true;
		strainerL->VRGripInterfaceSettings.bSimulateOnDrop=true;
		strainerL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		UE_LOG(LogTemp, Warning, TEXT("Grabbed Glass Strainer on Left"))			

	}
	
}

void APlayerCharacter::CheckDroppedObjectRight()
{
	// 오른손에 Tongs를 잡고 있었다면
	if(isGrabbingTongsRight)
	{
		// Tongs에 잡혀 있는 대상이 있었다면
		if(isGrabbingWithTongsRight)
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			auto tongCompRef = huchuTong->tongRight;
			UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(-9, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
			isTongsTickEnabled = true;
			// 1. 잡지않은 상태로 전환
			isGrabbingWithTongsRight = false;
			// 2. 손에서 떼어내기
			GrabbedObjectWithTongsRight->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			// 3. 물리기능 활성화
			GrabbedObjectWithTongsRight->SetSimulatePhysics(true);
			// 4. 충돌기능 활성화
			GrabbedObjectWithTongsRight->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GrabbedObjectWithTongsRight = nullptr;
		}
		else
		{
		}
		
		isGrabbingTongsRight=false;
	}
	else if(isGrabbingBottleRight)
	{
		isGrabbingBottleRight=false;
	}
	else if(isGrabbingTabletRight)
	{
		isGrabbingTabletRight=false;
		widgetInteractionComp->bShowDebug=false;
		widgetInteractionCompLeft->bShowDebug=false;
	}
	else if(isGrabbingCoasterRight)
	{
		isGrabbingCoasterRight=false;
	}
	else if(isGrabbingCupRight&&cup!=nullptr)
	{
		cup->isCupTickActivated=false;
		isGrabbingCupRight=false;
	}
	else if(isGrabbingShakerLidRight)
	{
		isGrabbingShakerLidRight=false;
		if(shakerLid!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dropped ShakerLid"))			
			shakerLid->AttachToShakerStrainer();		
		}
	}
	else if(isGrabbingShakerStrainerRight)
	{
		isGrabbingShakerStrainerRight=false;
		if(shakerStrainer!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dropped Shaker Strainer"))
			shakerStrainer->AttachToShaker();
		}
	}
	else if(isGrabbingMixingGlassRight)
	{
		isGrabbingMixingGlassRight=false;
	}
	else if(isGrabbingStrainerRight)
	{
		isGrabbingStrainerRight=false;
		if(strainer!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dropped Strainer"))
			strainer->AttachToMixingGlass();
		}
	}
	
}

void APlayerCharacter::CheckDroppedObjectLeft()
{
	// 왼손에 Tongs를 잡고 있었다면
	if(isGrabbingTongsLeft)
	{
		// Tongs에 잡혀 있는 대상이 있었다면
		if(isGrabbingWithTongsLeft)
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			auto tongCompRef = huchuTongL->tongRight;
			UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(-9, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
			isTongsTickEnabledL = true;
			// 1. 잡지않은 상태로 전환
			isGrabbingWithTongsLeft = false;
			// 2. 손에서 떼어내기
			GrabbedObjectWithTongsLeft->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			// 3. 물리기능 활성화
			GrabbedObjectWithTongsLeft->SetSimulatePhysics(true);
			// 4. 충돌기능 활성화
			GrabbedObjectWithTongsLeft->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GrabbedObjectWithTongsLeft = nullptr;
		}
		else
		{
		}

		isGrabbingTongsLeft=false;
	}
	else if(isGrabbingBottleLeft)
	{
		isGrabbingBottleLeft=false;
	}
	else if(isGrabbingTabletLeft)
	{
		isGrabbingTabletLeft=false;
		widgetInteractionComp->bShowDebug=false;
		widgetInteractionCompLeft->bShowDebug=false;
	}
	else if(isGrabbingCoasterLeft)
	{
		isGrabbingCoasterLeft=false;
	}
	else if(isGrabbingCupLeft&&cupL!=nullptr)
	{
		cupL->isCupTickActivated=false;
		isGrabbingCupLeft=false;
	}
	else if(isGrabbingShakerLidLeft)
	{
		isGrabbingShakerLidLeft=false;
		if(shakerLidL!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dropped ShakerLid"))			
			shakerLidL->AttachToShakerStrainer();		
		}
	}
	else if(isGrabbingShakerStrainerLeft)
	{
		isGrabbingShakerStrainerLeft=false;
		if(strainerL!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dropped Shaker Strainer"))
			shakerStrainerL->AttachToShaker();
		}
	}
	else if(isGrabbingMixingGlassLeft)
	{
		isGrabbingMixingGlassLeft=false;
	}
	else if(isGrabbingStrainerLeft)
	{
		isGrabbingStrainerLeft=false;
		if(strainerL!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dropped Strainer"))
			strainerL->AttachToMixingGlass();
		}
	}
}

void APlayerCharacter::FireRight()
{	
	if(widgetInteractionComp)
	{
		//UI에 이벤트를 전달하고 싶다.
		widgetInteractionComp->PressPointerKey(FKey(FName("LeftMouseButton")));
	}
	// 오른손에 Tongs를 쥐고 있다면
	if(isGrabbingTongsRight)
	{
		// 중심점
		FVector Center = huchuTong->tongRight->GetSocketLocation(FName("TongAttach"));
		// 충돌체크(구충돌)
		// 충돌한 물체를 기억할 배열
		TArray<FOverlapResult> HitObj;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(huchuTong);
		bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(TongsGrabRange), params);
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
			isGrabbingWithTongsRight = true;
			// 2.. 현재 손과 가장 가까운 대상과 이번에 검출할 대상과 더 가까운 대상이 있다면		
			// 필요속성 : 현재 가장 가까운 대상과 손과의 거리
			float ClosestDist = FVector::Dist(HitObj[Closest].GetActor()->GetActorLocation(), Center);
			// 필요속성 : 이번에 검출할 대상과 손과의 거리
			float NextDist = FVector::Dist(HitObj[i].GetActor()->GetActorLocation(), Center);

			// 3. 만약 이번 대상이 현재 대상보다 가깝다면,
			if (NextDist < ClosestDist)
			{

				// 가장 가까운 대상으로 변경하기
				Closest = i;
			}
		}		
		// ice cube 잡기에 성공했다면
		if (isGrabbingWithTongsRight&&HitObj[Closest].GetComponent()->IsSimulatingPhysics() == true)
		{
			GrabbedActorWithTongsRight=HitObj[Closest].GetComponent()->GetAttachmentRootActor();
			GrabbedObjectWithTongsRight = HitObj[Closest].GetComponent();
			iceCube=Cast<AIceCube>(GrabbedActorWithTongsRight);
			slicedLime=Cast<ASlicedLime>(GrabbedActorWithTongsRight);
			halfSlicedLime=Cast<AHalfSlicedLime>(GrabbedActorWithTongsRight);
			
			if(GrabbedActorWithTongsRight==iceCube&&iceCube!=nullptr)
			{
				isGrabbingIceWithTongsRight=true;
				GrabbedObjectWithTongsRight->SetSimulatePhysics(false);
				GrabbedObjectWithTongsRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);				
				GrabbedObjectWithTongsRight->AttachToComponent(huchuTong->tongRight,FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("TongGrabSizeSocket"));
			}
			else if(GrabbedActorWithTongsRight==slicedLime&&slicedLime!=nullptr)
			{
				isGrabbingLimeWithTongsRight=true;
				GrabbedObjectWithTongsRight->SetSimulatePhysics(false);
				GrabbedObjectWithTongsRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);				
				GrabbedObjectWithTongsRight->AttachToComponent(huchuTong->tongRight,FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LimeSocket"));
			}
			else if(GrabbedActorWithTongsRight==halfSlicedLime&&halfSlicedLime!=nullptr)
			{
				isGrabbingLimeWithTongsRight=true;
				GrabbedObjectWithTongsRight->SetSimulatePhysics(false);
				GrabbedObjectWithTongsRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);				
				GrabbedObjectWithTongsRight->AttachToComponent(huchuTong->tongRight,FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LimeSocket"));
			}
		}		
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.Linkage = 0;
			LatentInfo.UUID = 0; 
			auto tongCompRef = huchuTong->tongRight;
			auto tongLoc =  huchuTong->tongRight->GetSocketLocation(FName("TongGrabSizeSocket"));
			auto tongRightVector = huchuTong->GetActorForwardVector();
			FCollisionQueryParams params1;
			params1.AddIgnoredActor(huchuTong);  
			params1.AddIgnoredActor(this);				
			FHitResult leftTrace;
			FHitResult rightTrace;
			// Tongs 양쪽에서 LineTrace롤 통해 Grab할 대상의 크기를 측정한다.
			bool bHitR = GetWorld()->LineTraceSingleByChannel(rightTrace,tongLoc+tongRightVector*25.0f, tongLoc+tongRightVector*-25.0f, ECC_Visibility,params1);
			bool bHitL = GetWorld()->LineTraceSingleByChannel(leftTrace,tongLoc+tongRightVector*-25.0f, tongLoc+tongRightVector*25.0f, ECC_Visibility,params1);
			// LineTrace가 양쪽 모두 적중했다면
			if(bHitL&&bHitR)
			{
				if(isGrabbingIceWithTongsRight)
				{
					isTongsTickEnabled = false;
					// Left Impact Point와 Right Impact Point 사이의 간격을 도출한다
					//grabbingObjectSize = FVector::Dist(leftTrace.ImpactPoint, rightTrace.ImpactPoint);
					// grabbingObjectSize에 따라서 Tongs가 다물어질 정도를 결정한다.
					tongCompRef->SetRelativeRotation(FRotator(9, 0, 0));
					//UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(5, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
				}
				else if(isGrabbingLimeWithTongsRight)
				{
					isTongsTickEnabled = false;
					tongCompRef->SetRelativeRotation(FRotator(14, 0, 0));
					//UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(8, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
				}
			}
			// LineTrace가 적중하지 않았다면 -> 허공이라면
			else
			{
				// Oculus Trigger Input Value에 따른 Tongs Rotation 제어 Tick 활성화
				isTongsTickEnabled=true;
			}

	}	
	if(isGrabbingCupRight&&cup!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("set cup empty"))
		if(cup->contents>0)
		{
			cup->SetCupEmpty();
		}
	}
}

void APlayerCharacter::FireLeft()
{
	if(widgetInteractionCompLeft)
	{
		widgetInteractionCompLeft->PressPointerKey(FKey(FName("LeftMouseButton")));
	}
	// 왼손에 Tongs를 쥐고 있다면
	if(isGrabbingTongsLeft)
	{
		// 중심점
		FVector Center = huchuTongL->tongRight->GetSocketLocation(FName("TongAttach"));
		// 충돌체크(구충돌)
		// 충돌한 물체를 기억할 배열
		TArray<FOverlapResult> HitObj;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(huchuTongL);
		//DrawDebugSphere(GetWorld(), Center, TongsGrabRange, 30, FColor::Red, false, 2.0, 0, 0.1);
		bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(TongsGrabRange), params);
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
			isGrabbingWithTongsLeft = true;
			// 2.. 현재 손과 가장 가까운 대상과 이번에 검출할 대상과 더 가까운 대상이 있다면		
			// 필요속성 : 현재 가장 가까운 대상과 손과의 거리
			float ClosestDist = FVector::Dist(HitObj[Closest].GetActor()->GetActorLocation(), Center);
			// 필요속성 : 이번에 검출할 대상과 손과의 거리
			float NextDist = FVector::Dist(HitObj[i].GetActor()->GetActorLocation(), Center);

			// 3. 만약 이번 대상이 현재 대상보다 가깝다면,
			if (NextDist < ClosestDist)
			{

				// 가장 가까운 대상으로 변경하기
				Closest = i;
			}
		}

		// ice cube 잡기에 성공했다면
		if (isGrabbingWithTongsLeft&&HitObj[Closest].GetComponent()->IsSimulatingPhysics() == true)
		{
			GrabbedActorWithTongsLeft=HitObj[Closest].GetComponent()->GetAttachmentRootActor();
			GrabbedObjectWithTongsLeft = HitObj[Closest].GetComponent();
			iceCubeL=Cast<AIceCube>(GrabbedActorWithTongsLeft);
			slicedLimeL=Cast<ASlicedLime>(GrabbedActorWithTongsLeft);
			halfSlicedLimeL=Cast<AHalfSlicedLime>(GrabbedActorWithTongsLeft);
			if(GrabbedActorWithTongsLeft==iceCubeL&&iceCubeL!=nullptr)
			{
				isGrabbingIceWithTongsLeft=true;
				GrabbedObjectWithTongsLeft->SetSimulatePhysics(false);
				GrabbedObjectWithTongsLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				GrabbedObjectWithTongsLeft->AttachToComponent(huchuTongL->tongRight,FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("TongGrabSizeSocket"));
			}
			else if(GrabbedActorWithTongsLeft==slicedLimeL&&slicedLimeL!=nullptr)
			{
				isGrabbingLimeWithTongsLeft=true;
				GrabbedObjectWithTongsLeft->SetSimulatePhysics(false);
				GrabbedObjectWithTongsLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				GrabbedObjectWithTongsLeft->AttachToComponent(huchuTongL->tongRight,FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LimeSocket"));
			}
			else if(GrabbedActorWithTongsLeft==halfSlicedLimeL&&halfSlicedLimeL!=nullptr)
			{
				isGrabbingLimeWithTongsLeft=true;
				GrabbedObjectWithTongsLeft->SetSimulatePhysics(false);
				GrabbedObjectWithTongsLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				GrabbedObjectWithTongsLeft->AttachToComponent(huchuTongL->tongRight,FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LimeSocket"));
			}
		}	
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			auto tongCompRef = huchuTongL->tongRight;
			auto tongLoc =  huchuTongL->tongRight->GetSocketLocation(FName("TongGrabSizeSocket"));
			auto tongRightVector = huchuTongL->GetActorForwardVector();
			FCollisionQueryParams params1;
			params1.AddIgnoredActor(huchuTongL);  
			params1.AddIgnoredActor(this);				
			FHitResult leftTrace;
			FHitResult rightTrace;
			// Tongs 양쪽에서 LineTrace롤 통해 Grab할 대상의 크기를 측정한다.
			bool bHitR = GetWorld()->LineTraceSingleByChannel(rightTrace,tongLoc+tongRightVector*25.0f, tongLoc+tongRightVector*-25.0f, ECC_Visibility,params1);
			bool bHitL = GetWorld()->LineTraceSingleByChannel(leftTrace,tongLoc+tongRightVector*-25.0f, tongLoc+tongRightVector*25.0f, ECC_Visibility,params1);
			// LineTrace가 양쪽 모두 적중했다면
			if(bHitL&&bHitR)
			{
				if(isGrabbingIceWithTongsLeft)
				{
					isTongsTickEnabledL = false;
					// Left Impact Point와 Right Impact Point 사이의 간격을 도출한다
					//grabbingObjectSizeL = FVector::Dist(leftTrace.ImpactPoint, rightTrace.ImpactPoint);
					// grabbingObjectSize에 따라서 Tongs가 다물어질 정도를 결정한다.
					tongCompRef->SetRelativeRotation(FRotator(9, 0, 0));
					//UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(5, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
				}
				else if(isGrabbingLimeWithTongsLeft)
				{
					isTongsTickEnabledL = false;
					tongCompRef->SetRelativeRotation(FRotator(14, 0, 0));
					//UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(8, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
				}
			}
			// LineTrace가 적중하지 않았다면 -> 허공이라면
			else
			{
				// Oculus Trigger Input Value에 따른 Tongs Rotation 제어 Tick 활성화
				isTongsTickEnabledL=true;
			}

	}
		// 오른손에 Tongs를 쥐고 있지 않다면
		else
		{
			return;
		}
	if(isGrabbingCupLeft&&cupL!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("set cup empty"))
		if(cupL->contents>0)
		{
			cupL->SetCupEmpty();
		}
	}
}

void APlayerCharacter::FireReleasedRight()
{
	//클릭 버튼 떼어내기 위한 함수
	if (widgetInteractionComp)
	{
		widgetInteractionComp->ReleasePointerKey(FKey(FName("LeftMouseButton")));
	}
	if(isGrabbingTongsRight)
	{		
		// Tongs로 잡고 있는 대상이 있었다면
		if (isGrabbingWithTongsRight)
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.Linkage = 0;
			LatentInfo.UUID = 0; 
			auto tongCompRef = huchuTong->tongRight;
			if(isGrabbingIceWithTongsRight)
			{
				UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(-9, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
			}
			else if(isGrabbingLimeWithTongsRight)
			{
				UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(-14, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
			}
			isTongsTickEnabled = true;
			// 1. 잡지않은 상태로 전환
			isGrabbingWithTongsRight = false;
			isGrabbingIceWithTongsRight=false;
			isGrabbingLimeWithTongsRight=false;
			// 2. 손에서 떼어내기
			GrabbedObjectWithTongsRight->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			// 3. 물리기능 활성화
			GrabbedObjectWithTongsRight->SetSimulatePhysics(true);
			// 4. 충돌기능 활성화
			GrabbedObjectWithTongsRight->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GrabbedObjectWithTongsRight = nullptr;
		}
		// Tongs 로 잡고 있는 대상이 없었다면
		else
		{
			isGrabbingWithTongsRight = false;
			isGrabbingIceWithTongsRight=false;
			isGrabbingLimeWithTongsRight=false;
			isTongsTickEnabled = true;
		}	
	}
	else
	{
		return;
	}
}

void APlayerCharacter::FireReleasedLeft()
{
	if (widgetInteractionCompLeft)
	{
		widgetInteractionCompLeft->ReleasePointerKey(FKey(FName("LeftMouseButton")));
	}
	if(isGrabbingTongsLeft)
	{		
		// Tongs로 잡고 있는 대상이 있었다면
		if (isGrabbingWithTongsLeft)
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			auto tongCompRef = huchuTongL->tongRight;
			if(isGrabbingIceWithTongsLeft)
			{
				UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(-9, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
			}
			else if(isGrabbingLimeWithTongsLeft)
			{
				UKismetSystemLibrary::MoveComponentTo(tongCompRef, tongCompRef->GetRelativeLocation(), tongCompRef->GetRelativeRotation()+FRotator(-14, 0, 0), false, false, 0.0, false, EMoveComponentAction::Move, LatentInfo);
			}
			isTongsTickEnabledL = true;
			// 1. 잡지않은 상태로 전환
			isGrabbingWithTongsLeft = false;
			isGrabbingIceWithTongsLeft=false;
			isGrabbingLimeWithTongsLeft=false;
			// 2. 손에서 떼어내기
			GrabbedObjectWithTongsLeft->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			// 3. 물리기능 활성화
			GrabbedObjectWithTongsLeft->SetSimulatePhysics(true);
			// 4. 충돌기능 활성화
			GrabbedObjectWithTongsLeft->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GrabbedObjectWithTongsLeft = nullptr;
		}
		// Tongs 로 잡고 있는 대상이 없었다면
		else
		{
			isGrabbingWithTongsLeft = false;
			isGrabbingIceWithTongsLeft=false;
			isGrabbingLimeWithTongsLeft=false;
			isTongsTickEnabledL = true;
		}	
	}
	else
	{
		return;
	}
}
