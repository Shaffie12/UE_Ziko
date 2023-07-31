// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/SwordHit.h"

#include "Actors/BaseWeapon.h"
#include "Animation/AnimInstanceProxy.h"
#include "Characters/AI/BaseEnemy.h"
#include "Characters/Player/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

void USwordHit::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	
	UKismetSystemLibrary::SphereTraceSingle(MeshComp,MeshComp->GetSocketLocation("FX_Sword_Bottom"),MeshComp->GetSocketLocation("FX_Sword_Top"),
		15.0f,UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2),false,ToIgnore,EDrawDebugTrace::ForDuration,Out,true,
		FColor::Red,FColor::Green,-1);

	ABaseEnemy* HitEnemy = Cast<ABaseEnemy>(Out.Actor);
	if(HitEnemy)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if(Player)
			UGameplayStatics::ApplyDamage(HitEnemy,10.0f,
				Player->GetController(),Player,
				UDamageType::StaticClass());
			
	}
}
