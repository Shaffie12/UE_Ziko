// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAnimInstance.generated.h"


class ABaseCharacter;
class ABaseEnemy;

UCLASS()
class ZIKO_API UEnemyAnimInstance: public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UEnemyAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void UpdateAnimAttributes();
	float GetRotationAngle(const FVector& Velocity) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	ABaseCharacter* Target;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Animation Properties")
	ABaseEnemy* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	float RotationAngle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	bool Aggro;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation Properties")
	bool Stunned;
	
};
