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
	if(M_Attack_Basic && !IsBusy && CanDoAttack)
	{
		Aura->Deactivate();
		IsBusy=true;
		Channelling=false;
		AttackType = EAttackType::AT_Basic;
		Cast<ASwordBasic>(GetPrimaryWeapon())->DamageArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PlayAnimMontage(M_Attack_Basic);
		
		
	}
	
}

void APaladinCharacter::FirstAbilityAttack()
{
	Super::FirstAbilityAttack();
	if(M_Attack_First && !IsBusy && CanDoAttack && !Channelling)
	{
		IsBusy=true;
		Channelling = true;
		Aura->Activate();
		AttackType= EAttackType::AT_Ability1;
		PlayAnimMontage(M_Attack_First);
		//GetWorld()->GetLatentActionManager().AddNewAction(this,1,
			//new CompileDamage(this));
	}
}

void APaladinCharacter::SecondAbilityAttack()
{
	Super::SecondAbilityAttack();
	
	if(M_Attack_Second && !IsBusy && CanDoAttack)
	{
		IsBusy=true;
		Channelling=false;
		Aura->Deactivate();
		AttackType= EAttackType::AT_Ability2;
		PlayAnimMontage(M_Attack_Second);
		
	}
	
}






