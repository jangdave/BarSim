// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalCharacter.h"
#include "OldPalAnimInstance.h"
#include "OldPalFSM.h"
#include "OldPalOrderWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AOldPalCharacter::AOldPalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bodyComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("bodyComp"));
	bodyComp->SetupAttachment(GetMesh());

	ConstructorHelpers::FClassFinder<UAnimInstance> tempAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Jang/ABP_OldPalAnim.ABP_OldPalAnim_C'"));
	if(tempAnim.Succeeded())
	{
		bodyComp->SetAnimInstanceClass(tempAnim.Class);
	}
	
	oldPalFSM = CreateDefaultSubobject<UOldPalFSM>(TEXT("oldPalFSM"));

	oldPalWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("oldPalWidget"));
	oldPalWidget->SetupAttachment(GetMesh());
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AOldPalCharacter::BeginPlay()
{
	Super::BeginPlay();

	oldPalAnim = Cast<UOldPalAnimInstance>(bodyComp->GetAnimInstance());

	oldPal_UI = Cast<UOldPalOrderWidget>(oldPalWidget->GetUserWidgetObject());
}

// Called every frame
void AOldPalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOldPalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

