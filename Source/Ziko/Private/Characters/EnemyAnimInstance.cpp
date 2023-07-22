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
}

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Self = Cast<ABaseEnemy>(TryGetPawnOwner());
	check(Self)
	Target = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
	check(Target);
	
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Self && Target)
		UpdateAnimAttributes();
}


void UEnemyAnimInstance::UpdateAnimAttributes()
{
	const FVector& Velocity = Self->GetVelocity();

	Speed = Velocity.Size();
	RotationAngle = GetRotationAngle(Velocity);
	Aggro = Self->IsInRange(Target->GetActorLocation());
	
	
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
