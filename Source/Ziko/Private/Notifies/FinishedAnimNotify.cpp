// Fill out your copyright notice in the Description page of Project Settings.
#include "Ziko/Public/Notifies/FinishedAnimNotify.h"

#include "Actors/SwordBasic.h"
#include "Characters/Player/PaladinCharacter.h"

void UFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp!= nullptr && MeshComp->GetOwner()!= nullptr)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if(Player!=nullptr)
		{
			Player->IsAnimationBusy =false;
			const AMeleeOneHanded* Weapon  = Cast<AMeleeOneHanded>(Player->GetPrimaryWeapon());
			if(Weapon)
				Weapon->DamageArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				
		}
			
	}
}
