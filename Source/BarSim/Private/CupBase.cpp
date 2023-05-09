// Fill out your copyright notice in the Description page of Project Settings.


#include "CupBase.h"

#include "DropBase.h"
#include "IceCube.h"
#include "LimeDrop.h"
#include "MixedDrop.h"
#include "VorbisAudioInfo.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Sound/DialogueTypes.h"

// Sets default values
ACupBase::ACupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cupComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cup"));
	SetRootComponent(cupComp);
	cupComp->SetCollisionProfileName(FName("Check"));

	liquorComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquor"));
	liquorComp->SetupAttachment(cupComp);
	liquorComp->SetRelativeScale3D(FVector(0.01f));
	liquorComp->SetCollisionProfileName(FName("Contents"));
	liquorComp->SetVisibility(false);
	
	measureComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Measure"));
	measureComp->SetupAttachment(cupComp);
	measureComp->SetCollisionProfileName(FName("Cup"));
	measureComp->SetVisibility(false);

	igCheckerComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IGChecker"));
	igCheckerComp->SetupAttachment(cupComp);
	igCheckerComp->SetCollisionProfileName(FName("IGChecker"));
	igCheckerComp->SetVisibility(false);
}

// Called when the game starts or when spawned
void ACupBase::BeginPlay()
{
	Super::BeginPlay();

	cupSize = cupSizeOrigin;
	
	measureComp->OnComponentBeginOverlap.AddDynamic(this, &ACupBase::AddLiquor);
	igCheckerComp->OnComponentBeginOverlap.AddDynamic(this, &ACupBase::AddIce);
	igCheckerComp->OnComponentEndOverlap.AddDynamic(this, &ACupBase::ExtractIce);
}

// Called every frame
void ACupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//전체 부피 중 특정 액체가 차지하는 비율만큼 머테리얼 섞기
	//오더 어레이와 컨텐츠 어레이가 있을때만
	if(NameArray.Num() != 0 && ContentsArray.Num() != 0)
	{
		if(NameArray.Find(FString("Gin")) != INDEX_NONE)
		{
			ginInside = ContentsArray[NameArray.Find(FString("Gin"))];
		}
		
		if(NameArray.Find(FString("Lime")) != INDEX_NONE)
		{
			limeInside = ContentsArray[NameArray.Find(FString("Lime"))];
		}

		if(NameArray.Find(FString("Rum")) != INDEX_NONE)
		{
			rumInside = ContentsArray[NameArray.Find(FString("Rum"))];
		}

		if(NameArray.Find(FString("Sugar")) != INDEX_NONE)
		{
			sugarInside = ContentsArray[NameArray.Find(FString("Sugar"))];
		}

		if(NameArray.Find(FString("Vermouth")) != INDEX_NONE)
		{
			vermouthInside = ContentsArray[NameArray.Find(FString("Vermouth"))];
		}

		if(NameArray.Find(FString("Campari")) != INDEX_NONE)
		{
			campariInside = ContentsArray[NameArray.Find(FString("Campari"))];
		}

		if(NameArray.Find(FString("Whiskey")) != INDEX_NONE)
		{
			whiskeyInside = ContentsArray[NameArray.Find(FString("Whiskey"))];
		}
		
		allInside = ginInside + limeInside + rumInside + sugarInside + vermouthInside + campariInside + whiskeyInside;
		float opacity = FMath::Clamp(limeInside / allInside * 2 + whiskeyInside / allInside * 5 + campariInside / allInside * 8, 0.2, 0.8);

		liquorComp->SetScalarParameterValueOnMaterials(FName("Lime"), limeInside / allInside);
		liquorComp->SetScalarParameterValueOnMaterials(FName("Campari"), campariInside / allInside);
		liquorComp->SetScalarParameterValueOnMaterials(FName("Whiskey"), whiskeyInside / allInside);
		liquorComp->SetScalarParameterValueOnMaterials(FName("Opacity"), opacity);
	}

	//timePassed에 시간 누적
	timePassed += DeltaTime;

	//마지막으로 스터포인트 지나고 5초 지나면 stirRate 초기화
	if(timePassed >= 5.0f)
	{
		stirRate = 0;
	}
	
	//충분히 저어진 상태면
	if(stirRate >= stirNeeded)
	{
		if(!MixArray.IsEmpty())
		{
			for(int i = 0; i < MixArray.Num(); i++)
			{
				MixArray[i] = true;
			}
		}
		else
		{
			MixArray.Add(true);
		}
		bStirredLater = true;
	}
	
	//MixArray에 false값인 원소가 하나라도 있거나 비어 있으면
	if(MixArray.Find(false) != INDEX_NONE || MixArray.Num() == 0)
	{
		//안 섞인거
		bStirred = false;
	}
	//MixArray에 false 값인 원소가 하나도 없고 MixArray가 비어있지 않다면
	else
	{
		//섞인거
		bStirred = true;
	}

	//ShakeArray에 false값인 원소가 하나라도 있거나 비어 있으면
	if(ShakeArray.Find(false) != INDEX_NONE || ShakeArray.Num() == 0)
	{
		bShaked = false;
	}
	else
	{
		bShaked = true;
	}

}

void ACupBase::AddLiquor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	mixedDropOverlapped = Cast<AMixedDrop>(OtherActor);
	// 섞인 방울이 컵에 담기면
	if(mixedDropOverlapped)
	{
		overlappedNum ++;
		//방울에 NameArray가 있다면
		if(!mixedDropOverlapped->NameArray.IsEmpty())
		{
			for(int i = 0; i < mixedDropOverlapped->NameArray.Num(); i++)
			{
				//컵의 NameArray에 같은 이름을 가진 원소가 있다면
				if(NameArray.Find(mixedDropOverlapped->NameArray[i]) != INDEX_NONE)
				{
					//해당 원소의 순서의 ContentsArray이 가진 기존 배열값에 새 방울이 가진 ContentsArray 값을 더해줌
					ContentsArray[NameArray.Find(mixedDropOverlapped->NameArray[i])] = ContentsArray[NameArray.Find(mixedDropOverlapped->NameArray[i])] + mixedDropOverlapped->ContentsArray[i];
				}
				//컵의 NameArray에 같은 이름이 없다면
				else
				{
					//새로 추가
					NameArray.Emplace(mixedDropOverlapped->NameArray[i]);
					ContentsArray.Add(mixedDropOverlapped->ContentsArray[i]);
				}
			}
			MixArray.Add(mixedDropOverlapped->bStirred);
			ShakeArray.Add(mixedDropOverlapped->bShaked);
			contents = contents + mixedDropOverlapped->dropMass;
			insideContents = FMath::Clamp(contents, 0, cupSize);
			liquorComp->SetVisibility(true);
			LiquorScale();
			mixedDropOverlapped->Destroy();
		}
	}
	else
	{
		drop = Cast<ADropBase>(OtherActor);
		if(drop)
		{
			overlappedNum ++;
			//들어온 방울 액터가 가진 이름을 NameArrary에, 유량을 ContentsArray에 저장한다.
			if(!NameArray.IsEmpty())
			{
				//NameArray에 이미 저장된 이름이라면
				if(NameArray.Find(drop->name) != INDEX_NONE)
				{
					//해당 배열 순서의 ContentsArray에 기존값에 새로 오버랩된 방울 액터의 dropMass 값을 더해서 넣어주고
					ContentsArray[NameArray.Find(drop->name)] = ContentsArray[NameArray.Find(drop->name)] + drop->dropMass;
				}
				//NameArray에 저장되어 있지 않은 이름이라면 
				else
				{
					//새로운 NameArray와 ContentsArray에 넣는다.
					NameArray.Emplace(drop->name);
					ContentsArray.Add(drop->dropMass);
				}
			}
			else
				//배열이 비어있을 경우 값 하나 일단 넣기
				{
				NameArray.Emplace(drop->name);
				ContentsArray.Add(drop->dropMass);
				}
			contents = contents + drop->dropMass;
			insideContents = FMath::Clamp(contents, 0, cupSize);
			liquorComp->SetVisibility(true);
			LiquorScale();
			MixArray.Add(false);
			ShakeArray.Add(false);
			drop->Destroy();
			
		}
	}
	
}

void ACupBase::AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ice = Cast<AIceCube>(OtherActor);
	//igchecker에 얼음이 오버랩되었을 때
	if(ice)
	{
		iceCount += 1;
		//얼음 갯수 하나당 2온스씩 내부 용량 줄이기
		cupSize = cupSizeOrigin - iceCount * 2;
		insideContents = FMath::Clamp(contents, 0, cupSize);
		LiquorScale();
	}
}

void ACupBase::ExtractIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ice = Cast<AIceCube>(OtherActor);
	//igchecker에 얼음이 오버랩해제되었을 때
	if(ice)
	{
		iceCount -= 1;
		//얼음 갯수 하나당 2온스씩 내부 용량 줄이기
		cupSize = cupSizeOrigin - iceCount * 2;
		insideContents = FMath::Clamp(contents, 0, cupSize);
		LiquorScale();

	}
}

void ACupBase::LiquorScale()
{
	liquorComp->SetRelativeScale3D(FVector(1,1,insideContents / cupSize));
}

