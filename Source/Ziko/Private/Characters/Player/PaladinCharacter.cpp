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
	
	if(M_Attack_Basic && !IsBusy)
	{
		IsBusy=true;
		Cast<ASwordBasic>(GetPrimaryWeapon())->DamageArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PlayAnimMontage(M_Attack_Basic);
	}
	
}

void APaladinCharacter::FirstAbilityAttack()
{
	Super::FirstAbilityAttack();
	if(M_Attack_First && !IsBusy)
	{
		IsBusy=true;
		PlayAnimMontage(M_Attack_First);
	}
}

void APaladinCharacter::SecondAbilityAttack()
{
	Super::SecondAbilityAttack();
	if(M_Attack_Second && !IsBusy)
	{
		IsBusy=true;
		PlayAnimMontage(M_Attack_Second);
		
	}
	
}






