#include "Characters/Player/PaladinCharacter.h"
#include "Actors/SwordBasic.h"
#include "Characters/CharacterAnimInstance.h"

APaladinCharacter::APaladinCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
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
	Super::BaseAttack();
}

void APaladinCharacter::FirstAbilityAttack()
{
	Super::FirstAbilityAttack();
}

void APaladinCharacter::SecondAbilityAttack()
{
	Super::SecondAbilityAttack();
}






