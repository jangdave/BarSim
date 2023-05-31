// Fill out your copyright notice in the Description page of Project Settings.


#include "MartiniCup.h"

#include "HalfSlicedLime.h"
#include "OlivePick.h"
#include "SlicedLime.h"
#include "Kismet/GameplayStatics.h"

void AMartiniCup::LiquorScale()
{
	liquorComp->SetRelativeScale3D(FVector(insideContents / cupSize));
}

void AMartiniCup::AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AddIce(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	slicedLime = Cast<ASlicedLime>(OtherActor);
	halfSlicedLime = Cast<AHalfSlicedLime>(OtherActor);
	olive = Cast<AOlivePick>(OtherActor);
	//igchecker에 라임이 오버랩되었을 때
	if(slicedLime)
	{
		if(slicedLime->isSlicedLimeAttachable&&isLimeAttached==false)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
			slicedLime->DisableComponentsSimulatePhysics();
			slicedLime->SetActorEnableCollision(false);
			auto limeSocketTrans = cupComp->GetSocketTransform(FName("SlicedLimeSocket"));
			slicedLime->SetActorLocationAndRotation(limeSocketTrans.GetLocation(), limeSocketTrans.GetRotation());
			slicedLime->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("SlicedLimeSocket"));
			isLimeAttached = true;
		}
	}
	else if(halfSlicedLime)
	{
		if(halfSlicedLime->isHalfSlicedLimeAttachable&&isLimeAttached==false)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
			halfSlicedLime->DisableComponentsSimulatePhysics();
			halfSlicedLime->SetActorEnableCollision(false);
			auto halfLimeSocketTrans = cupComp->GetSocketTransform(FName("HalfSlicedLimeSocket"));
			halfSlicedLime->SetActorLocationAndRotation(halfLimeSocketTrans.GetLocation(), halfLimeSocketTrans.GetRotation());
			halfSlicedLime->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HalfSlicedLimeSocket"));
			isLimeAttached = true;
		}
	}
	//igchecker에 올리브가 오버랩되었을 때
	else if(olive)
	{
		//if(olive->isOliveAttachable&&isOliveAttached==false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Olive Attached"))
			UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
			olive->DisableComponentsSimulatePhysics();
			olive->SetActorEnableCollision(false);
			auto oliveSocketTrans = cupComp->GetSocketTransform(FName("OliveSocket"));
			olive->SetActorLocationAndRotation(oliveSocketTrans.GetLocation(), oliveSocketTrans.GetRotation());
			olive->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("OliveSocket"));
			isOliveAttached = true;
		}
	}

	
}
