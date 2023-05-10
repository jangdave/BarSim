// Fill out your copyright notice in the Description page of Project Settings.


#include "Tablet.h"
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

}

// Called every frame
void ATablet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

