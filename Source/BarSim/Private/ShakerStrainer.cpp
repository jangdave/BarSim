// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakerStrainer.h"

#include "Shaker.h"
#include "ShakerLid.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Materials/MaterialExpressionChannelMaskParameterColor.h"

// Sets default values
AShakerStrainer::AShakerStrainer()
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
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AShakerStrainer::LidOverlap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &AShakerStrainer::LidOverlapEnd);
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

void AShakerStrainer::LidOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	lid = Cast<AShakerLid>(OtherActor);

	if(lid)
	{
		lid->AttachToComponent(meshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("Lid"));
		lid->meshComp->SetCollisionProfileName(FName("Overlapped"));
		bLidOn = true;
	}
}

void AShakerStrainer::LidOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	lid = Cast<AShakerLid>(OtherActor);

	if(lid)
	{
		lid->meshComp->SetCollisionProfileName(FName("Strainer"));
		bLidOn = false;
		lid->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}
