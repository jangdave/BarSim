// Fill out your copyright notice in the Description page of Project Settings.


#include "RockGlass.h"

#include "HalfSlicedLime.h"
#include "HalfSlicedOrange.h"
#include "IceCube.h"
#include "OlivePick.h"
#include "SlicedLime.h"
#include "SlicedOrange.h"
#include "Kismet/GameplayStatics.h"

void ARockGlass::BeginPlay()
{
	Super::BeginPlay();

	igCheckerComp->OnComponentBeginOverlap.AddDynamic(this, &ARockGlass::AddIce);
}

void ARockGlass::AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	iceCubeR=Cast<AIceCube>(OtherActor);
	halfSlicedOrangeR=Cast<AHalfSlicedOrange>(OtherActor);
	slicedOrangeR=Cast<ASlicedOrange>(OtherActor);
	
	//igchecker에 얼음이 오버랩되었을 때
	if(iceCubeR)
	{
		if(iceCubeR->isIceCubeAttachable)
		{
			if(iceCount==0)
			{
				auto randPitch = FMath::FRandRange(0.95, 1.05);
				UGameplayStatics::PlaySound2D(GetWorld(), iceDropSound, 1, randPitch, 0);
				iceCubeR->DisableComponentsSimulatePhysics();	
				if(cupComp->IsSimulatingPhysics()==true)
				{
					
				}
				else
				{
					auto socketLoc1 = cupComp->GetSocketTransform(FName("IceSocket1"), RTS_World);
					iceCubeR->SetActorLocationAndRotation(socketLoc1.GetLocation(), socketLoc1.GetRotation());
				}
				iceCubeR->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("IceSocket1"));
				iceCount += 1;
				UE_LOG(LogTemp, Warning, TEXT("RockGlass : IceCount : %d"), iceCount);
				//얼음 갯수 하나당 2온스씩 내부 용량 줄이기
				cupSize = cupSizeOrigin - iceCount * 1.8;
				insideContents = FMath::Clamp(contents, 0, cupSize);
				LiquorScale();
			}
			else if(iceCount==1)
			{
				auto randPitch = FMath::FRandRange(0.95, 1.05);
				UGameplayStatics::PlaySound2D(GetWorld(), iceDropSound, 1, randPitch, 0);
				iceCubeR->DisableComponentsSimulatePhysics();
				if(cupComp->IsSimulatingPhysics()==true)
				{
					
				}
				else
				{
					auto socketLoc2 = cupComp->GetSocketTransform(FName("IceSocket2"), RTS_World);
					iceCubeR->SetActorLocationAndRotation(socketLoc2.GetLocation(), socketLoc2.GetRotation());
				}	
				iceCubeR->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("IceSocket2"));
				iceCount += 1;
				UE_LOG(LogTemp, Warning, TEXT("RockGlass : IceCount : %d"), iceCount);
				//얼음 갯수 하나당 2온스씩 내부 용량 줄이기
				cupSize = cupSizeOrigin - iceCount * 1.8;
				insideContents = FMath::Clamp(contents, 0, cupSize);
				LiquorScale();
			}
			else if(iceCount>=2)
			{
				
			}
		}
	}
		//igchecker에 오렌지가 오버랩되었을 때
		else if(slicedOrangeR)
		{
			if(slicedOrangeR->isSlicedOrangeAttachable&&isOrangeAttached==false)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
				slicedOrangeR->DisableComponentsSimulatePhysics();
				slicedOrangeR->SetActorEnableCollision(false);	
				auto limeSocketTrans = cupComp->GetSocketTransform(FName("SlicedOrangeSocket"));
				slicedOrangeR->SetActorLocationAndRotation(limeSocketTrans.GetLocation(), limeSocketTrans.GetRotation());
				slicedOrangeR->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("SlicedOrangeSocket"));
				isOrangeAttached = true;
				garnishArray[2]=true;
			}
		}
		else if(halfSlicedOrangeR)
		{
			if(halfSlicedOrangeR->isHalfSlicedOrangeAttachable&&isOrangeAttached==false)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
				halfSlicedOrangeR->DisableComponentsSimulatePhysics();
				halfSlicedOrangeR->SetActorEnableCollision(false);
				auto halfLimeSocketTrans = cupComp->GetSocketTransform(FName("HalfSlicedOrangeSocket"));
				halfSlicedOrangeR->SetActorLocationAndRotation(halfLimeSocketTrans.GetLocation(), halfLimeSocketTrans.GetRotation());				
				halfSlicedOrangeR->AttachToComponent(cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HalfSlicedOrangeSocket"));
				isOrangeAttached = true;
				garnishArray[2]=true;
			}
		}
	
}
