// Fill out your copyright notice in the Description page of Project Settings.


#include "Tablet.h"

#include "TabletStand.h"
#include "TabletWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATablet::ATablet(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(29, 20, 1));
	
	tabletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tabletMesh"));
	tabletMesh->SetupAttachment(boxComp);
	
	widgetComp=CreateDefaultSubobject<UWidgetComponent>("widgetComp");
	widgetComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ATablet::BeginPlay()
{
	Super::BeginPlay();

	tablet_UI = Cast<UTabletWidget>(widgetComp->GetUserWidgetObject());
}

// Called every frame
void ATablet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATablet::AttachToTabletStand()
{
	FVector Center = tabletMesh->GetComponentLocation();
	TArray<FOverlapResult> HitObj;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(25), params);
	if (bHit == false)
	{
		return;
	}
	for(int i=0; i<HitObj.Num(); ++i)
	{
		tabletStand = Cast<ATabletStand>(HitObj[i].GetActor());
		{
			if(tabletStand)
			{
				isTabletStandCasted = true;
				tabletStandArrayNum = i;
				UE_LOG(LogTemp, Warning, TEXT("Casting Success"))
			}
		}
	}
	if(isTabletStandCasted)
	{
		tabletStand=Cast<ATabletStand>(HitObj[tabletStandArrayNum].GetActor());
		if(tabletStand!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attach Activated"))
			this->DisableComponentsSimulatePhysics();
			this->VRGripInterfaceSettings.bSimulateOnDrop=false;
			auto standLoc = tabletStand->meshComp->GetSocketTransform(FName("TabletSocket"));
			this->SetActorLocationAndRotation(standLoc.GetLocation(), standLoc.GetRotation());
			this->AttachToComponent(tabletStand->meshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("TabletSocket"));
			
			isTabletStandCasted=false;
			HitObj.Reset();
		}
	}
}

