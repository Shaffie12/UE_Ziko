#include "Characters/Player/PaladinCharacter.h"
#include "Actors/SwordBasic.h"
#include "Characters/CharacterAnimInstance.h"
#include "Engine.h"
APaladinCharacter::APaladinCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AppliedDamage=false;
	IsBusy=false;
}

void APaladinCharacter::BeginPlay()
{
	
	Super::BeginPlay();
}

void APaladinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APaladinCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APaladinCharacter::BaseAttack()
{
	Super::BaseAttack();
	if(IsArmed())
	{
		const ABaseWeapon* const HeldWeapon = GetPrimaryWeapon();
		const int8 AttackEnergyCost = HeldWeapon->GetAttackCost(EAttackType::AT_Basic);
		if (EnergyVal < AttackEnergyCost) return;

		if(M_Attack_Basic && !IsBusy)
		{
			IsBusy=true;
			Cast<ASwordBasic>(GetPrimaryWeapon())->DamageArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			PlayAnimMontage(M_Attack_Basic);
		}
		EnergyVal -= AttackEnergyCost;
	}
}

void APaladinCharacter::FirstAbilityAttack()
{
	//should uncheck busy
	Super::FirstAbilityAttack();
}

void APaladinCharacter::SecondAbilityAttack()
{
	Super::SecondAbilityAttack();
}






