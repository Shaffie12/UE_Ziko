// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyAnimInstance.h"

#include "Characters/AI/BaseEnemy.h"
#include "Characters/Player/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ABaseEnemy>(TryGetPawnOwner());
	Target = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController());
	Aggro = false;
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Character)
		UpdateAnimAttributes();
	else
		Character = Cast<ABaseEnemy>(TryGetPawnOwner());
}

void UEnemyAnimInstance::UpdateAnimAttributes()
{
	const FVector& Velocity = Character->GetVelocity();
	
	Speed = Velocity.Size();
	RotationAngle = GetRotationAngle(Velocity);
	//fix aggro anim
	
}

float UEnemyAnimInstance::GetRotationAngle(const FVector& Velocity) const
{
	FVector Char = Character ->GetActorForwardVector();
	float Angle = UKismetMathLibrary::Acos(FVector::DotProduct(Char, Velocity.GetSafeNormal()));
	float Sign = FVector::CrossProduct(Char,Velocity.GetSafeNormal()).Z;
	Angle = Angle * 180.0f/PI;
	Sign<0? Angle = -Angle: Angle;
	
	return (Angle);
}
