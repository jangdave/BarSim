// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerCharacter.h"
#include "CustomerAnimInstance.h"
#include "CustomerFSM.h"
#include "SpawnManager.h"
#include "Kismet/GameplayStatics.h"

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
	
	ConstructorHelpers::FClassFinder<UAnimInstance> tempAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Jang/ABP_CustomerAnimInstance.ABP_CustomerAnimInstance_C'"));
	if(tempAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnim.Class);
	}
	
	costomerFSM = CreateDefaultSubobject<UCustomerFSM>(TEXT("costomerFSM"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ACustomerCharacter::BeginPlay()
{
	Super::BeginPlay();

	customerAnim = Cast<UCustomerAnimInstance>(GetMesh()->GetAnimInstance());

	spawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	
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
	int32 idx = SetRandRange(1, 10);

	// 5보다 크면 여자
	if(idx > 5)
	{
		int32 womanIdx = SetRandRange(0, 2);

		// 전에 나온 것과 똑같지 않으면
		if(womanIdx != spawnManager->checkCount)
		{
			GetMesh()->SetSkeletalMesh(womenMesh[womanIdx].Object);
			
			spawnManager->checkCount = womanIdx;
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
		int32 manIdx = SetRandRange(0, 2);

		// 전에 나온 것과 똑같지 않으면
		if(manIdx != spawnManager->checkCount)
		{
			GetMesh()->SetSkeletalMesh(manMesh[manIdx].Object);
			
			spawnManager->checkCount = manIdx;
		}
		// 똑같다면
		else
		{
			SetMesh();
		}
	}
}

// 랜덤 함수
int32 ACustomerCharacter::SetRandRange(int32 idxStart, int32 idxEnd)
{
	int32 result = FMath::RandRange(idxStart, idxEnd);

	return result;
}

