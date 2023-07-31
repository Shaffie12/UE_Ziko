#include "Characters/Player/PaladinCharacter.h"
#include "Actors/SwordBasic.h"
#include "Characters/CharacterAnimInstance.h"
#include "Engine.h"

APaladinCharacter::APaladinCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APaladinCharacter::BeginPlay()
{
	Super::BeginPlay();
	Channelling=false;
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
	if(M_Attack_Basic && CanDoAttack && !IsAnimationBusy)
	{
		Aura->Deactivate();
		IsAnimationBusy=true;
		Channelling=false;
		AttackType = EAttackType::AT_Basic;
		const ASwordBasic* PrimaryWeapon = Cast<ASwordBasic>(GetPrimaryWeapon());
		if(PrimaryWeapon)
			PlayAnimMontage(M_Attack_Basic);
		
	}
	
}

void APaladinCharacter::FirstAbilityAttack()
{
	Super::FirstAbilityAttack();
	if(M_Attack_First && CanDoAttack && !IsAnimationBusy && !Channelling)
	{
		IsAnimationBusy=true;
		Channelling = true;
		Aura->Activate();
		AttackType= EAttackType::AT_Ability1;
		PlayAnimMontage(M_Attack_First);
	}
}

void APaladinCharacter::SecondAbilityAttack()
{
	Super::SecondAbilityAttack();
	
	if(M_Attack_Second && !IsAnimationBusy)
	{
		IsAnimationBusy=true;
		Channelling=false;
		Aura->Deactivate();
		AttackType= EAttackType::AT_Ability2;
		PlayAnimMontage(M_Attack_Second);
		
	}
	
}






