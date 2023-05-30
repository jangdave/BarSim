// Fill out your copyright notice in the Description page of Project Settings.


#include "Strainer.h"

#include "MixingGlass.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStrainer::AStrainer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetCollisionProfileName(FName("Strainer"));
	meshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AStrainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStrainer::AttachToMixingGlass()
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
		mixingGlass = Cast<AMixingGlass>(HitObj[i].GetActor());
		{
			if(mixingGlass)
			{
				isMixingGlassCasted = true;
				mixingGlassArrayNum = i;
				UE_LOG(LogTemp, Warning, TEXT("Casting Success"))
			}
		}
	}
	if(isMixingGlassCasted)
	{
		mixingGlass=Cast<AMixingGlass>(HitObj[mixingGlassArrayNum].GetActor());
		if(mixingGlass!=nullptr)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), attachSound, 1, 1, 0);
			UE_LOG(LogTemp, Warning, TEXT("Attach Activated"))
			this->DisableComponentsSimulatePhysics();
			this->VRGripInterfaceSettings.bSimulateOnDrop=false;
			auto strainerLoc = mixingGlass->cupComp->GetSocketTransform(FName("Strainer"));
			this->SetActorLocationAndRotation(strainerLoc.GetLocation(), strainerLoc.GetRotation());
			this->AttachToComponent(mixingGlass->cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Strainer"));
			//lid->meshComp->SetCollisionProfileName(FName("Overlapped"));
			mixingGlass->DisableComponentsSimulatePhysics();
			mixingGlass->bStrainerOn=true;
			isMixingGlassCasted=false;
			HitObj.Reset();
		}
	}
}

