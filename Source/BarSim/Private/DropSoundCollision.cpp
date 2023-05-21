// Fill out your copyright notice in the Description page of Project Settings.


#include "DropSoundCollision.h"

#include "BarSpoon.h"
#include "BottleBase.h"
#include "Coaster.h"
#include "CupBase.h"
#include "HuchuTong.h"
#include "IceCube.h"
#include "MixingGlass.h"
#include "Shaker.h"
#include "ShakerLid.h"
#include "ShakerStrainer.h"
#include "Strainer.h"
#include "Tablet.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADropSoundCollision::ADropSoundCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boxComp=CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	
}


// Called when the game starts or when spawned
void ADropSoundCollision::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ADropSoundCollision::OnOverlap);
}

// Called every frame
void ADropSoundCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropSoundCollision::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Overlapped Actor Cast
	huchuTong=Cast<AHuchuTong>(OtherActor);
	bottle = Cast<ABottleBase>(OtherActor);
	tablet = Cast<ATablet>(OtherActor);
	coaster=Cast<ACoaster>(OtherActor);
	cup=Cast<ACupBase>(OtherActor);
	barSpoon=Cast<ABarSpoon>(OtherActor);
	strainer=Cast<AStrainer>(OtherActor);
	shakerStrainer=Cast<AShakerStrainer>(OtherActor);
	shakerLid=Cast<AShakerLid>(OtherActor);
	shaker=Cast<AShaker>(OtherActor);
	mixingGlass=Cast<AMixingGlass>(OtherActor);
	iceCube=Cast<AIceCube>(OtherActor);

	auto randPitch = FMath::FRandRange(0.9, 1.1);

	if(huchuTong)
	{
		if(huchuTong->isDropSoundEnabled==true)
		{
			auto huchuTongLoc = huchuTong->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), huchuTongDropSound, huchuTongLoc, 0.7, randPitch, 0);
			huchuTong->isDropSoundEnabled=false;
		}
	}
	else if(bottle)
	{
		if(bottle->isDropSoundEnabled==true)
		{
			auto bottleLoc = bottle->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), bottleDropSound, bottleLoc, 1, randPitch, 0);
			bottle->isDropSoundEnabled=false;
		}
	}
	else if(tablet)
	{
		if(tablet->isDropSoundEnabled==true)
		{
			auto tabletLoc = tablet->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), tabletDropSound, tabletLoc, 1, randPitch, 0);
			tablet->isDropSoundEnabled=false;
		}
	}
	else if(cup)
	{
		if(cup->isDropSoundEnabled==true)
		{
			auto cupLoc = cup->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), cupDropSound, cupLoc, 1, randPitch, 0);
			cup->isDropSoundEnabled=false;
		}
	}
	else if(coaster)
	{
		if(coaster->isDropSoundEnabled==true)
		{
			auto coasterLoc = coaster->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), coasterDropSound, coasterLoc, 1, randPitch, 0);
			coaster->isDropSoundEnabled=false;
		}
	}
	else if(barSpoon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spoon drop"))
		if(barSpoon->isDropSoundEnabled==true)
		{
			auto barSpoonLoc = barSpoon->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), barSpoonDropSound, barSpoonLoc, 1, randPitch, 0);
			barSpoon->isDropSoundEnabled=false;
		}
	}
	else if(strainer)
	{
		if(strainer->isDropSoundEnabled==true)
		{
			auto strainerLoc = strainer->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), strainerDropSound, strainerLoc, 1, randPitch, 0);
			strainer->isDropSoundEnabled=false;
		}
	}
	else if(shakerStrainer)
	{
		if(shakerStrainer->isDropSoundEnabled==true)
		{
			auto shakerStrainerLoc = shakerStrainer->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), shakerStrainerDropSound, shakerStrainerLoc, 1, randPitch, 0);
			shakerStrainer->isDropSoundEnabled=false;
		}
	}
	else if(shakerLid)
	{
		if(shakerLid->isDropSoundEnabled==true)
		{
			auto shakerLidLoc = shakerLid->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), shakerLidDropSound, shakerLidLoc, 1, randPitch, 0);
			shakerLid->isDropSoundEnabled=false;
		}
	}
	else if(shaker)
	{
		if(shaker->isDropSoundEnabledS==true)
		{
			auto shakerLoc = shaker->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), shakerDropSound, shakerLoc, 1, randPitch, 0);	
			shaker->isDropSoundEnabledS=false;
		}
	}
	else if(mixingGlass)
	{
		if(mixingGlass->isDropSoundEnabledM==true)
		{
			auto mixingGlassLoc = mixingGlass->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), mixingGlassDropSound, mixingGlassLoc, 1, randPitch, 0);
			mixingGlass->isDropSoundEnabledM=false;
		}
	}
	else if(iceCube)
	{
		if(iceCube->isDropSoundEnabled==true)
		{
			auto iceCubeLoc = iceCube->GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), iceCubeDropSound, iceCubeLoc, 1, randPitch, 0);
			iceCube->isDropSoundEnabled=false;
		}
	}
}
