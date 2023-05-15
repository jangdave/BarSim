// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakerStrainer.h"

#include "Shaker.h"
#include "ShakerLid.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Materials/MaterialExpressionChannelMaskParameterColor.h"

// Sets default values
AShakerStrainer::AShakerStrainer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);

	splineComp = CreateDefaultSubobject<USplineComponent>(TEXT("splineComp"));
	splineComp->SetupAttachment(meshComp);

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	sphereComp->SetupAttachment(meshComp);
	sphereComp->SetSphereRadius(3.0f);
	sphereComp->SetRelativeLocation(FVector(0,0,7.7f));
	sphereComp->SetCollisionProfileName(FName("StrainerCheck"));
}

// Called when the game starts or when spawned
void AShakerStrainer::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AShakerStrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector splineLoc = splineComp->GetComponentLocation();
	streamPoint = splineComp->FindLocationClosestToWorldLocation(FVector(splineLoc.X, splineLoc.Y, 0), ESplineCoordinateSpace::World);
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), streamPoint.X, streamPoint.Y, streamPoint.Z);
	DrawDebugSphere(GetWorld(), streamPoint, 0.3f, 32, FColor::Blue, false);
}

void AShakerStrainer::AttachToShaker()
{
	FVector Center = meshComp->GetComponentLocation();
	TArray<FOverlapResult> HitObj;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	DrawDebugSphere(GetWorld(), Center, 10, 30, FColor::Red, false, 2.0, 0, 0.1);
	bool bHit = GetWorld()->OverlapMultiByChannel(HitObj, Center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(10), params);
	if (bHit == false)
	{
		return;
	}
	for(int i=0; i<HitObj.Num(); ++i)
	{
		shaker = Cast<AShaker>(HitObj[i].GetActor());
		{
			if(shaker)
			{
				isStrainerCasted = true;
				shakerArrayNum = i;
				UE_LOG(LogTemp, Warning, TEXT("Casting Success"))
			}
		}
	}
	if(isStrainerCasted)
	{
		shaker=Cast<AShaker>(HitObj[shakerArrayNum].GetActor());
		if(shaker!=nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attach Activated"))
			this->DisableComponentsSimulatePhysics();
			this->VRGripInterfaceSettings.bSimulateOnDrop=false;
			auto shakerLoc = shaker->sphereComp->GetSocketTransform(FName("Strainer"));
			this->SetActorLocationAndRotation(shakerLoc.GetLocation(), shakerLoc.GetRotation());
			this->AttachToComponent(shaker->sphereComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Strainer"));
			//lid->meshComp->SetCollisionProfileName(FName("Overlapped"));
			shaker->DisableComponentsSimulatePhysics();
			shaker->bStrainerOn=true;
			isStrainerCasted=false;
			this->VRGripInterfaceSettings.bDenyGripping=true;
			HitObj.Reset();
		}
	}
}


