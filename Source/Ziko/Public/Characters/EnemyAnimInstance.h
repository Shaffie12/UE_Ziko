// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UCLASS()
class ZIKO_API UEnemyAnimInstance: public UAnimInstance
{
	GENERATED_BODY()
public:
	UEnemyAnimInstance();
	virtual void NativeInitializeAnimation() override;

private:
	void UpdateAnimAttributes();

};
