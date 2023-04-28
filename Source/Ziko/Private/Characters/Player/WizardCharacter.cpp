// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/WizardCharacter.h"

#include "Actors/MagicWand.h"

// Sets default values
AWizardCharacter::AWizardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWizardCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->HideBoneByName(FName("weapon_l"),EPhysBodyOp::PBO_None);
	
}

// Called every frame
void AWizardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWizardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWizardCharacter::BaseAttack()
{
	Super::BaseAttack();
	if (AttackType != EAttackType::AT_None) return;
	
	ABaseWeapon* const MagicWand = GetPrimaryWeapon();
	if (!MagicWand) return;

	const int8 AttackEnergyCost = MagicWand->GetAttackCost(EAttackType::AT_Basic);
	if (EnergyVal < AttackEnergyCost) return;
	
	AttackType = EAttackType::AT_Basic;
	GetWorldTimerManager().SetTimer(AttackTimer, MagicWand, &ABaseWeapon::BaseAttack, BaseAttackWaitRate, false);
	
	EnergyVal -= AttackEnergyCost;
}

void AWizardCharacter::FirstAbilityAttack()
{	
	Super::FirstAbilityAttack();
	if (AttackType != EAttackType::AT_None) return;
	
	ABaseWeapon* const Wand = GetPrimaryWeapon();
	if (!Wand) return;

	const int8 AttackEnergyCost = Wand->GetAttackCost(EAttackType::AT_Ability1);
	if (EnergyVal < AttackEnergyCost) return;

	AttackType = EAttackType::AT_Ability1;
	GetWorldTimerManager().SetTimer(AttackTimer, Wand, &ABaseWeapon::FirstAbilityAttack, BaseAttackWaitRate, false);
	
	EnergyVal -= AttackEnergyCost;
}

void AWizardCharacter::SecondAbilityAttack()
{
	Super::SecondAbilityAttack();
	if (AttackType != EAttackType::AT_None) return;

	ABaseWeapon* const MagicWand = GetPrimaryWeapon();
	if (!MagicWand) return;

	const int8 AttackEnergyCost = MagicWand->GetAttackCost(EAttackType::AT_Ability2);
	if (EnergyVal < AttackEnergyCost) return;

	AttackType = EAttackType::AT_Ability2;
	GetWorldTimerManager().SetTimer(AttackTimer, MagicWand, &ABaseWeapon::SecondAbilityAttack, BaseAttackWaitRate, false);
	
	EnergyVal -= AttackEnergyCost;
}
