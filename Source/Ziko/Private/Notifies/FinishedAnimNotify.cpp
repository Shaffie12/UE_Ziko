// Fill out your copyright notice in the Description page of Project Settings.
#include "Ziko/Public/Notifies/FinishedAnimNotify.h"

#include "Actors/SwordBasic.h"
#include "Characters/Player/PaladinCharacter.h"

void UFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(MeshComp!= nullptr && MeshComp->GetOwner()!= nullptr)
	{
		APaladinCharacter* Player = Cast<APaladinCharacter>(MeshComp->GetOwner());
		if(Player!=nullptr)
		{
			Player->IsBusy =false;
			if(Player->GetPrimaryWeapon()!=nullptr)
			{
				Cast<ASwordBasic>(Player->GetPrimaryWeapon())->DamageArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Player->AppliedDamage=false;
			}
				
				
		}
			
	}
}
