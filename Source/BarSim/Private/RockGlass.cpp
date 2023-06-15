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
}

void ARockGlass::AddIce(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ice=Cast<AIceCube>(OtherActor);
	HalfSlicedOrange=Cast<AHalfSlicedOrange>(OtherActor);
	SlicedOrange=Cast<ASlicedOrange>(OtherActor);
	
	//igchecker에 얼음이 오버랩되었을 때
	if(ice)
	{
		if(ice->isIceCubeAttachable)
		{
			if(iceCount==0)
			{
				auto randPitch = FMath::FRandRange(0.95, 1.05);
				UGameplayStatics::PlaySound2D(GetWorld(), iceDropSound, 1, randPitch, 0);
				ice->DisableComponentsSimulatePhysics();	
				auto socketLoc1 = this->cupComp->GetSocketTransform(FName("IceSocket1"), RTS_World);
				ice->SetActorLocationAndRotation(socketLoc1.GetLocation(), socketLoc1.GetRotation());				
				ice->AttachToComponent(this->cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("IceSocket1"));
				iceRef1=ice;
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
				ice->DisableComponentsSimulatePhysics();
				auto socketLoc2 = this->cupComp->GetSocketTransform(FName("IceSocket2"), RTS_World);
				ice->SetActorLocationAndRotation(socketLoc2.GetLocation(), socketLoc2.GetRotation());					
				ice->AttachToComponent(this->cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("IceSocket2"));
				iceRef2=ice;
				//iceRef1->iceCubeMesh->SetCollisionProfileName(FName("IceAttached"));
				//iceRef2->iceCubeMesh->SetCollisionProfileName(FName("IceAttached"));
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
		else if(SlicedOrange)
		{
			if(SlicedOrange->isSlicedOrangeAttachable&&isOrangeAttached==false)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
				SlicedOrange->DisableComponentsSimulatePhysics();
				SlicedOrange->SetActorEnableCollision(false);	
				auto limeSocketTrans = this->cupComp->GetSocketTransform(FName("SlicedOrangeSocket"));
				SlicedOrange->SetActorLocationAndRotation(limeSocketTrans.GetLocation(), limeSocketTrans.GetRotation());
				SlicedOrange->AttachToComponent(this->cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("SlicedOrangeSocket"));
				slicedOrangeRef=SlicedOrange;
				isOrangeAttached = true;
				garnishArray[2]=true;
			}
		}
		else if(HalfSlicedOrange)
		{
			if(HalfSlicedOrange->isHalfSlicedOrangeAttachable&&isOrangeAttached==false)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), limeAttachSound, 1, 1, 0);
				HalfSlicedOrange->DisableComponentsSimulatePhysics();
				HalfSlicedOrange->SetActorEnableCollision(false);
				auto halfLimeSocketTrans = this->cupComp->GetSocketTransform(FName("HalfSlicedOrangeSocket"));
				HalfSlicedOrange->SetActorLocationAndRotation(halfLimeSocketTrans.GetLocation(), halfLimeSocketTrans.GetRotation());				
				HalfSlicedOrange->AttachToComponent(this->cupComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HalfSlicedOrangeSocket"));
				halfSlicedOrangeRef=HalfSlicedOrange;
				isOrangeAttached = true;
				garnishArray[2]=true;
			}
		}
	
}
