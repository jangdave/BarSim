// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "Chair.h"
#include "CustomerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	// 인스턴스 상에 있는 모든 의자를 배열에 담는다
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChair::StaticClass(), chairs);

	// bIsSit 이라는 bool 배열에 의자 클래스의 변수를 담는다
	for(int i = 0; i<chairs.Num(); i++)
	{
		auto temp = Cast<AChair>(chairs[i]);
		bIsSit.Add(temp->bCheck);
	}

	// 시간이 지날때마다 손님을 스폰한다
	FTimerHandle spawnTime;
	GetWorldTimerManager().SetTimer(spawnTime, this, &ASpawnManager::SpawnCustom, 2, true);
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsCoctail.Empty();
	bIsPlayer.Empty();
	bIsCoaster.Empty();
	
	for(int i = 0; i<chairs.Num(); i++)
	{
		auto temp = Cast<AChair>(chairs[i]);
		bIsCoctail.Add(temp->bCheckCoctail);
		bIsCoaster.Add(temp->bCheckCoaster);
		bIsPlayer.Add(temp->bCheckPlayer);
	}
}

void ASpawnManager::SpawnCustom()
{
	for(int i = 0; i<bIsSit.Num(); i++)
	{
		if(bIsSit[i] != true)
		{
			bCheckSit = true;
		}
	}
	if(bCheckSit != false)
	{
		GetWorld()->SpawnActor<ACustomerCharacter>(customerFactory, GetActorLocation(), GetActorRotation());

		bCheckSit = false;
	}
}

