// Fill out your copyright notice in the Description page of Project Settings.


#include "BarSpoon.h"

#include <Imath/Deploy/Imath-3.1.3/include/Imath/ImathFun.h>

#include "CupBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABarSpoon::ABarSpoon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);
	meshComp->SetCollisionProfileName(FName("Spoon"));	
}

// Called when the game starts or when spawned
void ABarSpoon::BeginPlay()
{
	Super::BeginPlay();
	meshComp->OnComponentBeginOverlap.AddDynamic(this, &ABarSpoon::OnFluidOverlap);
	meshComp->OnComponentEndOverlap.AddDynamic(this, &ABarSpoon::OffFluidOverlap);

	if(rotCurve)
	{
		FOnTimelineFloat TimelineCallback;
		TimelineCallback.BindDynamic(this, &ABarSpoon::TurnSpoon);
		timeline.AddInterpFloat(rotCurve, TimelineCallback);
	}
}

// Called every frame
void ABarSpoon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 컵 안의 액체와 스푼이 오버랩 되어 있다면
	if(bCupOverlapped)
	{
		// 회전값 고정
		if(cup)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Spoon Overlapped"));
			//FVector cupDir = cup->GetActorLocation() - GetActorLocation();
			//FRotator cupRot = cupDir.Rotation();
			//SetActorRotation(FRotator(0, cupRot.Yaw, 0));
		}
	}
	else
	//액체에서 나오면
	{
		//손에 있는 소켓 회전값으로 고정-------------------------------------------------------
		//SetActorRotation(FRotator(0,0,0));
	}

}

void ABarSpoon::OnFluidOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	cup = Cast<ACupBase>(OtherActor);
	if(cup)
	{
		//timeline.Play();
		if(OtherComp == cup->liquorComp)
		{
			bCupOverlapped = true;
		}
	}
}

void ABarSpoon::OffFluidOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	cup = Cast<ACupBase>(OtherActor);
	if(cup)
	{
		//timeline.Reverse();
		if(OtherComp == cup->liquorComp)
		{
			bCupOverlapped = false;
		}
	}
}

void ABarSpoon::TurnSpoon(float Output)
{
	FVector cupDir = cup->GetActorLocation() - GetActorLocation();
	FRotator cupRot = cupDir.Rotation();
	FRotator facingCup = FRotator(0, cupRot.Yaw, 0);
	UE_LOG(LogTemp, Warning, TEXT("spoon Rotate"));
	SetActorRotation(UKismetMathLibrary::RLerp(FRotator(0.0f), facingCup, Output, true));
}