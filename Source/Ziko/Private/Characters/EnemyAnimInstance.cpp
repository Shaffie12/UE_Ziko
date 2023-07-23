// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyAnimInstance.h"

#include "DrawDebugHelpers.h"
#include "Characters/AI/BaseEnemy.h"
#include "Characters/Player/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Aggro = false;
	IsAttacking = false;
}

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Elapsed =0.f;
	AttackAnimValue=0;
	Self = Cast<ABaseEnemy>(TryGetPawnOwner());
	check(Self)
	Target = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
	check(Target);
	
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Self && Target)
		UpdateAnimAttributes(DeltaSeconds);
}


void UEnemyAnimInstance::UpdateAnimAttributes(float& DT)
{
	const FVector& Velocity = Self->GetVelocity();

	Speed = Velocity.Size();
	RotationAngle = GetRotationAngle(Velocity);
	Aggro = Self->IsInAggroRange(Target->GetActorLocation());
	IsAttacking = Self->IsAttacking();
	if(IsAttacking && Elapsed>=AttackAnimationChangeWait)
	{
		AttackAnimValue = SelectAttackAnimationValue();
		Elapsed=0.f;
	}
	else
		Elapsed+= DT;
	
}

float UEnemyAnimInstance::GetRotationAngle(const FVector& Velocity) const
{
	FVector Char = Self ->GetActorForwardVector();
	float Angle = UKismetMathLibrary::Acos(FVector::DotProduct(Char, Velocity.GetSafeNormal()));
	float Sign = FVector::CrossProduct(Char,Velocity.GetSafeNormal()).Z;
	Angle = Angle * 180.0f/PI;
	Sign<0? Angle = -Angle: Angle;
	
	return (Angle);
}

//will throw exception or not select values properly if != 3 animations are used in the animator
int UEnemyAnimInstance::SelectAttackAnimationValue()
{
	return FMath::RandRange(0,2);
}
