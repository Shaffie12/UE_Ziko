#include "Characters/Player/PaladinCharacter.h"
#include "Actors/SwordBasic.h"
#include "Characters/CharacterAnimInstance.h"

APaladinCharacter::APaladinCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	UsableWeaponType = EWeaponType::WP_Melee1Handed;
	
}

void APaladinCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	GetMesh()->HideBoneByName(TEXT("sword_bottom"),EPhysBodyOp::PBO_None);
	GetMesh()->HideBoneByName(TEXT("sword_top"),EPhysBodyOp::PBO_None);
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
	if(IsArmed())
	{
		const ABaseWeapon* const HeldWeapon = GetPrimaryWeapon();
		const int8 AttackEnergyCost = HeldWeapon->GetAttackCost(EAttackType::AT_Basic);
		if (EnergyVal < AttackEnergyCost) return;

		if(M_Attack_Basic)
		{
			PlayAnimMontage(M_Attack_Basic);
		}
		EnergyVal -= AttackEnergyCost;
	}
}

void APaladinCharacter::FirstAbilityAttack()
{
	if(IsArmed())
	{
		const ABaseWeapon* const HeldWeapon = GetPrimaryWeapon();
		const int8 AttackEnergyCost = HeldWeapon->GetAttackCost(EAttackType::AT_Basic);
		if (EnergyVal < AttackEnergyCost) return;

		if(M_Attack_Basic)
		{
			PlayAnimMontage(M_Attack_First);
		}
		EnergyVal -= AttackEnergyCost;
	}
}

void APaladinCharacter::SecondAbilityAttack()
{
	if(IsArmed())
	{
		const ABaseWeapon* const HeldWeapon = GetPrimaryWeapon();
		const int8 AttackEnergyCost = HeldWeapon->GetAttackCost(EAttackType::AT_Basic);
		if (EnergyVal < AttackEnergyCost) return;

		if(M_Attack_Basic)
		{
			PlayAnimMontage(M_Attack_Second);
		}
		EnergyVal -= AttackEnergyCost;
	}
}






