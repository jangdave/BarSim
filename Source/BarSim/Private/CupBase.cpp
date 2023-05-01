// Fill out your copyright notice in the Description page of Project Settings.


#include "CupBase.h"

#include "DropBase.h"
#include "IceCube.h"
#include "LimeDrop.h"
#include "VorbisAudioInfo.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialParameterCollection.h"

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
	if(OrderArray.Num() != 0 && ContentsArray.Num() != 0)
	{
		// 내용물 초기화
		ginInside = 0;
		limeInside = 0;
		//오더 어레이 중 Gin 이라는 값을 가진 배열 원소의 순서를 구함
		for(int i = 0; i < OrderArray.Num(); i++)
		{
			if(OrderArray[i] == FString("Gin"))
			{
				//GinArray.Add(i);
				ginInside = ginInside + ContentsArray[i];
			}
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f"), ginInside);

		//오더 어레이 중 Lime 이라는 값을 가진 배열 원소의 순서를 구함
		for(int i = 0; i < OrderArray.Num(); i++)
		{
			if(OrderArray[i] == FString("Lime"))
			{
				//GinArray.Add(i);
				limeInside = limeInside + ContentsArray[i];
			}
		}
		//UE_LOG(LogTemp, Warning, TEXT("%f"), limeInside)

		float all = ginInside + limeInside;
		
		liquorComp->SetScalarParameterValueOnMaterials(FName("Lime"), limeInside / all);
	}

}

void ACupBase::AddLiquor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	drop = Cast<ADropBase>(OtherActor);

	if(drop)
	{
		overlappedNum ++;
		//들어온 방울 액터가 가진 이름을 OrderArrary에, 유량을 ContentsArray에 저장한다.
		//OrderArray 배열의 마지막 원소와 현재 닿은 물방울의 이름이 같다면
		if(!OrderArray.IsEmpty())
		{
			if(OrderArray[OrderArray.Num()-1] == drop->name)
			{
				//들어온 방울 액터의 이름이 마지막 배열 원소의 이름과 같다면 그 배열에 ContentsArray에 더한다.
				ContentsArray[ContentsArray.Num()-1] += drop->dropMass;
			}
			else
			{
				//들어온 방울 액터의 이름이 마지막 배열 원소의 이름과 다르다면 다음 원소로 orderArray와 ContentsArray를 넣는다.
				OrderArray.Emplace(drop->name);
				ContentsArray.Add(drop->dropMass);
			}
		}
		else
			//배열이 비어있을 경우 값 하나 일단 넣기
		{
			OrderArray.Emplace(drop->name);
			ContentsArray.Add(drop->dropMass);
		}
		contents = contents + drop->dropMass;
		insideContents = FMath::Clamp(contents, 0, cupSize);
		liquorComp->SetVisibility(true);
		LiquorScale();
		//UE_LOG(LogTemp, Warning, TEXT("%f"), insideContents);
		drop->Destroy();
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

