// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

#include "Ziko.h"
#include "Chaos/CollisionResolutionUtil.h"
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
	const FVector& Velocity = Character->GetVelocity();
	
	Speed = Velocity.Size();
	bIsMoving = Velocity.Size() > 0.5f;
	RotationAngle = GetRotationAngle(Velocity);
	bIsAlive = Character->IsAlive();
	bIsArmed = Character->IsArmed();
	bIsAttacking = Character->GetAttackState() != EAttackType::AT_None;
	AttackType = Character->GetAttackState();
}
float UCharacterAnimInstance::GetRotationAngle(const FVector& Velocity) const
{
	FVector Char = Character ->GetActorForwardVector();
	float Angle = UKismetMathLibrary::Acos(FVector::DotProduct(Char, Velocity.GetSafeNormal()));
	float Sign = FVector::CrossProduct(Char,Velocity.GetSafeNormal()).Z;
	Angle = Angle * 180.0f/PI;
	Sign<0? Angle = -Angle: Angle;
	
	return (Angle);
}