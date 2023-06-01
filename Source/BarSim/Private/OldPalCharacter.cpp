// Fill out your copyright notice in the Description page of Project Settings.


#include "OldPalCharacter.h"
#include "Coaster.h"
#include "CupBase.h"
#include "OldPalAnimInstance.h"
#include "OldPalFSM.h"
#include "OldPalOrderWidget.h"
#include "PlayerCharacter.h"
#include "SpawnManager.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	oldPalWidget->SetupAttachment(GetCapsuleComponent());
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AOldPalCharacter::BeginPlay()
{
	Super::BeginPlay();

	oldPalAnim = Cast<UOldPalAnimInstance>(bodyComp->GetAnimInstance());

	oldPal_UI = Cast<UOldPalOrderWidget>(oldPalWidget->GetUserWidgetObject());

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), enterSound, GetActorLocation(), GetActorRotation());
}

// Called every frame
void AOldPalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(oldPalFSM->player != nullptr)
	{
		FVector tar = oldPalWidget->GetComponentLocation();
		FVector direction = oldPalFSM->player->VRReplicatedCamera->GetComponentLocation();
		FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(tar,direction);
		oldPalWidget->SetWorldRotation(FMath::Lerp(oldPalWidget->GetComponentRotation(), lookAtRotation, 0.1f));
	}
}

// Called to bind functionality to input
void AOldPalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOldPalCharacter::BindOldPalOverlap()
{
	TArray<FOverlapResult> hitsInfo;
	FVector centerLoc = bodyComp->GetSocketLocation(TEXT("hand_rSocket"));
	FQuat centerRot = bodyComp->GetSocketQuaternion(TEXT("hand_rSocket"));
	FCollisionObjectQueryParams params;
	FCollisionShape checkShape = FCollisionShape::MakeSphere(20);
	params.AddObjectTypesToQuery(ECC_GameTraceChannel9);
	
	GetWorld()->OverlapMultiByObjectType(hitsInfo, centerLoc, centerRot, params, checkShape);
	for(FOverlapResult hitInfo : hitsInfo)
	{
		cup = Cast<ACupBase>(hitInfo.GetActor());

		// 컵이 오버랩 되면
		if(cup != nullptr)
		{
			// 컵의 물리를 끄고
			cup->cupComp->SetSimulatePhysics(false);

			// 컵을 손에 붙인다
			cup->AttachToComponent(bodyComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_rSocket");
		}
	}

	// 디버그 라인
	DrawDebugSphere(GetWorld(), centerLoc, 20, 1, FColor::Yellow, false, 1);
}

void AOldPalCharacter::DetachCup()
{
	// 컵을 떨어트리고
	cup->DetachAllSceneComponents(bodyComp, FDetachmentTransformRules::KeepWorldTransform);

	// 컵의 물리를 킨다
	cup->cupComp->SetSimulatePhysics(true);

	FTimerHandle setloc;
	GetWorldTimerManager().SetTimer(setloc, FTimerDelegate::CreateLambda([&]()
	{
		FVector targetLoc = oldPalFSM->spawnManager->aChairs[oldPalFSM->idx]->coctailBoxComp->GetComponentLocation();

		cup->SetActorLocation(FVector(targetLoc.X, targetLoc.Y, cup->GetActorLocation().Z));

		oldPalFSM->spawnManager->aChairs[oldPalFSM->idx]->coaster->SetActorLocation(FVector(targetLoc.X, targetLoc.Y, oldPalFSM->spawnManager->aChairs[oldPalFSM->idx]->coaster->GetActorLocation().Z));
	}), 1.0f, false);
}

