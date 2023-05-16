// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterAnimInstance.h"
#include "Math/UnrealMathUtility.h"
#include "Ziko.h"
#include "Chaos/CollisionResolutionUtil.h"
#include "Characters/Player/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

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
	RotationAngle = GetRotationAngle(Velocity);
	bIsAlive = Character->IsAlive();
	bIsArmed = Character->IsArmed();
	bIsAttacking = Character->GetAttackState() != EAttackType::AT_None;
	AttackType = Character->GetAttackState();
}
//it doesnt appear to get the char right and fwd vectors properly.
float UCharacterAnimInstance::GetRotationAngle(const FVector& Velocity) const
{
	FVector VelToMouse = 
	(Character->GetTransform().GetLocation() + Velocity) - (Character->GetTransform().GetLocation() + Character->GetActorForwardVector());
	//UE_LOG(LogTemp,Warning,TEXT("vel %f"),Velocity.X);
	return  VelToMouse.Rotation().Yaw;
}