// Fill out your copyright notice in the Description page of Project Settings.


#include "MartiniCup.h"

#include "HalfSlicedLime.h"
#include "IceCube.h"
#include "OlivePick.h"
#include "SlicedLime.h"
#include "Kismet/GameplayStatics.h"

void AMartiniCup::BeginPlay()
{
	Super::BeginPlay();

}

void AMartiniCup::LiquorScale()
{
	liquorComp->SetRelativeScale3D(FVector(insideContents / cupSize));
}

void AMartiniCup::AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	slicedLimeM = Cast<ASlicedLime>(OtherActor);
	halfSlicedLimeM = Cast<AHalfSlicedLime>(OtherActor);
	olive = Cast<AOlivePick>(OtherActor);
	iceCubeM=Cast<AIceCube>(OtherActor);	
	//igchecker에 라임이 오버랩되었을 때
	if(slicedLimeM)
	{
		if(slicedLimeM->isSlicedLimeAttachable&&isLimeAttached==false)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
			slicedLimeM->DisableComponentsSimulatePhysics();
			slicedLimeM->SetActorEnableCollision(false);
			auto limeSocketTrans = cupComp->GetSocketTransform(FName("SlicedLimeSocket"));
			slicedLimeM->SetActorLocationAndRotation(limeSocketTrans.GetLocation(), limeSocketTrans.GetRotation());
			slicedLimeM->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("SlicedLimeSocket"));
			isLimeAttached = true;
			garnishArray[0]=true;
		}
	}
	else if(halfSlicedLimeM)
	{
		if(halfSlicedLimeM->isHalfSlicedLimeAttachable&&isLimeAttached==false)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
			halfSlicedLimeM->DisableComponentsSimulatePhysics();
			halfSlicedLimeM->SetActorEnableCollision(false);
			auto halfLimeSocketTrans = cupComp->GetSocketTransform(FName("HalfSlicedLimeSocket"));
			halfSlicedLimeM->SetActorLocationAndRotation(halfLimeSocketTrans.GetLocation(), halfLimeSocketTrans.GetRotation());
			halfSlicedLimeM->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HalfSlicedLimeSocket"));
			isLimeAttached = true;
			garnishArray[0]=true;
		}
	}
	//igchecker에 올리브가 오버랩되었을 때
	else if(olive)
	{
		if(olive->isOliveAttachable&&isOliveAttached==false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Olive Attached"))
			UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
			olive->DisableComponentsSimulatePhysics();
			olive->SetActorEnableCollision(false);
			auto oliveSocketTrans = cupComp->GetSocketTransform(FName("OliveSocket"));
			olive->SetActorLocationAndRotation(oliveSocketTrans.GetLocation(), oliveSocketTrans.GetRotation());
			olive->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("OliveSocket"));
			isOliveAttached = true;
			garnishArray[1]=true;
		}
	}
	else if(iceCubeM)
	{
		return;
	}

	
}
