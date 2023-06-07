// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerCharacter.h"

#include "Coaster.h"
#include "CupBase.h"
#include "CustomerAnimInstance.h"
#include "CustomerFSM.h"
#include "CustomerOrderWidget.h"
#include "SpawnManager.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACustomerCharacter::ACustomerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 여성 스켈레탈 메쉬
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Jang/Scanned3DPeoplePack/RP_Character/rp_carla_rigged_001_ue4/rp_carla_rigged_001_ue4.rp_carla_rigged_001_ue4'"));
	if(tempMesh.Succeeded())
	{
		womenMesh.Add(tempMesh);
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh1(TEXT("/Script/Engine.SkeletalMesh'/Game/Jang/Scanned3DPeoplePack/RP_Character/rp_claudia_rigged_002_ue4/rp_claudia_rigged_002_ue4.rp_claudia_rigged_002_ue4'"));
	if(tempMesh1.Succeeded())
	{
		womenMesh.Add(tempMesh1);
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/Jang/Scanned3DPeoplePack/RP_Character/rp_sophia_rigged_003_ue4/rp_sophia_rigged_003_ue4.rp_sophia_rigged_003_ue4'"));
	if(tempMesh2.Succeeded())
	{
		womenMesh.Add(tempMesh2);
	}

	// 남성 스켈레탈 메쉬
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh3(TEXT("/Script/Engine.SkeletalMesh'/Game/Jang/Scanned3DPeoplePack/RP_Character/rp_eric_rigged_001_ue4/rp_eric_rigged_001_ue4.rp_eric_rigged_001_ue4'"));
	if(tempMesh3.Succeeded())
	{
		manMesh.Add(tempMesh3);
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh4(TEXT("/Script/Engine.SkeletalMesh'/Game/Jang/Scanned3DPeoplePack/RP_Character/rp_manuel_rigged_001_ue4/rp_manuel_rigged_001_ue4.rp_manuel_rigged_001_ue4'"));
	if(tempMesh4.Succeeded())
	{
		manMesh.Add(tempMesh4);
	}
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh5(TEXT("/Script/Engine.SkeletalMesh'/Game/Jang/Scanned3DPeoplePack/RP_Character/rp_nathan_rigged_003_ue4/rp_nathan_rigged_003_ue4.rp_nathan_rigged_003_ue4'"));
	if(tempMesh5.Succeeded())
	{
		manMesh.Add(tempMesh5);
	}
	
	ConstructorHelpers::FClassFinder<UAnimInstance> tempAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Jang/ABP_CustomerAnim.ABP_CustomerAnim_C'"));
	if(tempAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnim.Class);
	}

	customerFSM = CreateDefaultSubobject<UCustomerFSM>(TEXT("costomerFSM"));

	orderWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("orderWidget"));
	orderWidget->SetupAttachment(GetCapsuleComponent());
		
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ACustomerCharacter::BeginPlay()
{
	Super::BeginPlay();

	customerAnim = Cast<UCustomerAnimInstance>(GetMesh()->GetAnimInstance());

	order_UI = Cast<UCustomerOrderWidget>(orderWidget->GetUserWidgetObject());
	
	SetMesh();
}

// Called every frame
void ACustomerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomerCharacter::SetMesh()
{
	int32 idx = customerFSM->SetRandRange(1, 8);

	// 5보다 크면 여자
	if(idx > 4)
	{
		int32 womanIdx = customerFSM->SetRandRange(0, 2);

		// 전에 나온 것과 똑같지 않으면
		if(womanIdx != customerFSM->spawnManager->checkMeshCount)
		{
			GetMesh()->SetSkeletalMesh(womenMesh[womanIdx].Object);

			if(womanIdx == 0 || womanIdx == 1)
			{
				GetMesh()->SetRelativeScale3D(FVector(1, 1, 1.1));
			}
			
			voiceCount = idx;
			
			customerFSM->spawnManager->checkMeshCount = womanIdx;
		}
		// 똑같다면
		else
		{
			SetMesh();
		}
	}
	// 5보다 작거나 같으면 남자
	else
	{
		int32 manIdx = customerFSM->SetRandRange(0, 2);

		// 전에 나온 것과 똑같지 않으면
		if(manIdx != customerFSM->spawnManager->checkMeshCount)
		{
			GetMesh()->SetSkeletalMesh(manMesh[manIdx].Object);

			GetMesh()->SetRelativeScale3D(FVector(1, 1, 1.03));
			
			voiceCount = idx;
			
			customerFSM->spawnManager->checkMeshCount = manIdx;
		}
		// 똑같다면
		else
		{
			SetMesh();
		}
	}
}

void ACustomerCharacter::BindOverlap()
{
	TArray<FOverlapResult> hitsInfo;
	FVector centerLoc = GetMesh()->GetSocketLocation(TEXT("hand_rSocket"));
	FQuat centerRot = GetMesh()->GetSocketQuaternion(TEXT("hand_rSocket"));
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
			cup->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_rSocket");
		}
	}

	// 디버그 라인
	DrawDebugSphere(GetWorld(), centerLoc, 20, 1, FColor::Yellow, false, 1);
}

void ACustomerCharacter::DetachCup()
{
	// 컵을 떨어트리고
	cup->DetachAllSceneComponents(GetMesh(), FDetachmentTransformRules::KeepWorldTransform);

	// 컵의 물리를 킨다
	cup->cupComp->SetSimulatePhysics(true);

	FTimerHandle setloc;
	GetWorldTimerManager().SetTimer(setloc, FTimerDelegate::CreateLambda([&]()
	{
		FVector targetLoc = customerFSM->spawnManager->aChairs[customerFSM->idx]->coctailBoxComp->GetComponentLocation();

		cup->SetActorLocation(FVector(targetLoc.X, targetLoc.Y, cup->GetActorLocation().Z));

		customerFSM->spawnManager->aChairs[customerFSM->idx]->coaster->SetActorLocation(FVector(targetLoc.X, targetLoc.Y, customerFSM->spawnManager->aChairs[customerFSM->idx]->coaster->GetActorLocation().Z));
	}), 1.0f, false);
}
