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
	Aura=FindComponentByClass<UParticleSystemComponent>();
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
	const int8 AttackEnergyCost = GetPrimaryWeapon()->GetAttackCost(EAttackType::AT_Basic);
	if (EnergyVal < AttackEnergyCost) return;
	if(M_Attack_Basic && !IsBusy)
	{
		Aura->Deactivate();
		IsBusy=true;
		AttackType = EAttackType::AT_Basic;
		Cast<ASwordBasic>(GetPrimaryWeapon())->DamageArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PlayAnimMontage(M_Attack_Basic);
		GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Magenta,FString::Printf(TEXT("ENERGY: %f"),EnergyVal));
		
	}
	
}

void APaladinCharacter::FirstAbilityAttack()
{
	Super::FirstAbilityAttack();
	if(M_Attack_First && !IsBusy)
	{
		IsBusy=true;
		Aura->Activate();
		AttackType= EAttackType::AT_Ability1;
		PlayAnimMontage(M_Attack_First);
	}
}

void APaladinCharacter::SecondAbilityAttack()
{
	Super::SecondAbilityAttack();
	Aura->Deactivate();
	AttackType= EAttackType::AT_Ability2;
	if(M_Attack_Second && !IsBusy)
	{
		IsBusy=true;
		PlayAnimMontage(M_Attack_Second);
		
	}
	
}






