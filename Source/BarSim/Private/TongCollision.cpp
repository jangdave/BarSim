// Fill out your copyright notice in the Description page of Project Settings.


#include "TongCollision.h"

#include "HuchuTong.h"
#include "Components/BoxComponent.h"

// Sets default values
ATongCollision::ATongCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tongCol = CreateDefaultSubobject<UBoxComponent>(TEXT("tongCol"));
	SetRootComponent(tongCol);

	tongCol->SetBoxExtent(FVector(10.0f));
	tongCol->SetGenerateOverlapEvents(true);


}

// Called when the game starts or when spawned
void ATongCollision::BeginPlay()
{
	Super::BeginPlay();

	tongCol->OnComponentBeginOverlap.AddDynamic(this, &ATongCollision::OnOverlap);
	tongCol->SetGenerateOverlapEvents(true);

	SetLifeSpan(0.02f);
}

// Called every frame
void ATongCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATongCollision::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bFromSweep = true;
	actorScale = SweepResult.GetActor()->GetActorScale3D();
	compScale = SweepResult.GetComponent()->GetComponentScale();
	auto attachedComponent = SweepResult.GetComponent();
	auto attachedActor = SweepResult.GetActor();
	if(attachedComponent!=nullptr&&huchuTongRef!=nullptr)
	{
		attachedComponent->K2_AttachToComponent(huchuTongRef->tongRight, TEXT("TongAttach"),EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,EAttachmentRule::KeepRelative,false);

	}
	if(attachedActor!=nullptr&&huchuTongRef!=nullptr)
	{
		attachedActor->K2_AttachToComponent(huchuTongRef->tongRight, TEXT("TongAttach"),EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,EAttachmentRule::KeepRelative,false);

	}

}

