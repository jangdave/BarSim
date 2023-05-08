// Fill out your copyright notice in the Description page of Project Settings.


#include "ShakerStrainer.h"

#include "Shaker.h"
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

