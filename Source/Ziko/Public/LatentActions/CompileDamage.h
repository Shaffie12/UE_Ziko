// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LatentActions.h"
#include "Characters/Player/PaladinCharacter.h"

class APaladinCharacter;

/**
 * 
 */
class ZIKO_API CompileDamage : public FPendingLatentAction
{

	float CompiledDamage;
	APaladinCharacter* Player;
	
public:
	CompileDamage(APaladinCharacter* Player): CompiledDamage(0.f), Player(Player){};
	virtual void UpdateOperation(FLatentResponse& Response) override;
};
