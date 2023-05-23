// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakerLid.h"

#include "ShakerStrainer.h"

// Sets default values
AShakerLid::AShakerLid(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
	meshComp->SetSimulatePhysics(true);
	meshComp->SetCollisionProfileName(FName("Strainer"));
}

// Called when the game starts or when spawned
void AShakerLid::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShakerLid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShakerLid::AttachToShakerStrainer()
{
	FVector Center = meshComp->GetComponentLocation();
	TArray<FOverlapResult> HitObj;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	//DrawDebugSphere(GetWorld(), Center, 10, 30, FColor::Red, false, 2.0, 0, 0.1);
	bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(10), params);
	if (bHit == false)
	{
		return;
	}
	for(int i=0; i<HitObj.Num(); ++i)
	{
		shakerStrainer = Cast<AShakerStrainer>(HitObj[i].GetActor());
		{
			if(shakerStrainer)
			{
				isShakerStrainerCasted = true;
				StrainerArrayNum = i;
				UE_LOG(LogTemp, Warning, TEXT("Casting Success"))
			}
		}
	}
	if(isShakerStrainerCasted)
	{
		shakerStrainer=Cast<AShakerStrainer>(HitObj[StrainerArrayNum].GetActor());
		if(shakerStrainer!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attach Activated"))
			this->DisableComponentsSimulatePhysics();
			this->VRGripInterfaceSettings.bSimulateOnDrop=false;
			auto lidLoc = shakerStrainer->meshComp->GetSocketTransform(FName("Lid"));
			this->SetActorLocationAndRotation(lidLoc.GetLocation(), lidLoc.GetRotation());
			this->AttachToComponent(shakerStrainer->meshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Lid"));

			//튕겨나가지 않게 콜리전 프리셋 설정
			meshComp->SetCollisionProfileName(FName("Overlapped"));
			//shakerStrainer->DisableComponentsSimulatePhysics();
			shakerStrainer->bLidOn=true;
			isShakerStrainerCasted=false;
			HitObj.Reset();
		}
	}
}

