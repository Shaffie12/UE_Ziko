// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterAnimInstance.h"

#include "Ziko.h"
#include "Chaos/CollisionResolutionUtil.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/Player/BaseCharacter.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
	Character = nullptr;
	Speed = 0.f;
	RotationAngle = 0.f;
	bIsAlive = true;
	bIsArmed = false;
	bIsAttacking = false;
	AttackType = EAttackType::AT_None;
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//check(Character);	//FIXME: Sometimes character = nullptr although it succeeded initially + not reassigned

	if (Character)
		UpdateAnimAttributes();
	else
		Character = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::UpdateAnimAttributes()
{
	const FVector& Direction = Character->GetVelocity();
	
	Speed = Direction.Size();
	RotationAngle = GetRotationAngle(Direction);
	bIsAlive = Character->IsAlive();
	bIsArmed = Character->IsArmed();
	bIsAttacking = Character->GetAttackState() != EAttackType::AT_None;
	AttackType = Character->GetAttackState();
}

float UCharacterAnimInstance::GetRotationAngle(const FVector& Direction) const
{
	const FTransform& CharacterTrans = Character->GetTransform(); 
	const FVector LocalDir = UKismetMathLibrary::InverseTransformDirection(CharacterTrans, Direction);
	const FRotator LocalRot = LocalDir.Rotation();
	
	return LocalRot.Yaw;
}