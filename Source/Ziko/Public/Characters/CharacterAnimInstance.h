// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Ziko.h"
#include "CharacterAnimInstance.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class ZIKO_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCharacterAnimInstance();
	
protected:
	/*Acts as BeginPlay*/
	virtual void NativeInitializeAnimation() override;

	/*Acts as Tick*/
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void UpdateAnimAttributes();
	
	float GetRotationAngle(const FVector& Direction) const;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	ABaseCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	float RotationAngle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	bool bIsAlive;		//FIXME: use bit field instead 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	bool bIsArmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	EAttackType AttackType;
};
