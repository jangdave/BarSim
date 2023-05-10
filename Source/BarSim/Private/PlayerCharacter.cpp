// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GripMotionControllerComponent.h"
#include "HuchuTong.h"
#include "Components/WidgetInteractionComponent.h"


APlayerCharacter::APlayerCharacter()
{
	widgetInteractionComp = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("widgetInteractionComp"));
	widgetInteractionComp->SetupAttachment(RightMotionController);


	
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
			subSystem->AddMappingContext(IMC_Hand, 0);
		}
	}

	widgetInteractionComp->DebugSphereLineThickness=0.5f;
	widgetInteractionComp->DebugLineThickness=0.3f;
	widgetInteractionComp->DebugColor=FColor::Red;
	widgetInteractionComp->bEnableHitTesting=true;
	widgetInteractionComp->bShowDebug=false;	
	widgetInteractionComp->InteractionDistance=50.0f;
	
}



void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


		//UE_LOG(LogTemp, Warning, TEXT("%f"), fingerPressedActionValue)
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::CheckGrabbedObjectRight()
{
	TArray<FBPActorGripInformation> RightGripArray;
	RightMotionController->GetAllGrips(RightGripArray);
	for(int i=0; i<RightGripArray.Num(); ++i)
	{
		GrabbedActorRight = RightGripArray[i].GetGrippedActor();
	}

	huchuTong=Cast<AHuchuTong>(GrabbedActorRight);
	// 잡은 대상이 Tongs라면
	if(GrabbedActorRight==huchuTong&&huchuTong!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabbed Huchu Right"));
	}
	
}

void APlayerCharacter::CheckGrabbedObjectLeft()
{
}
