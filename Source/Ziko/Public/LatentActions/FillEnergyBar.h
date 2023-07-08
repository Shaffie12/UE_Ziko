// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LatentActions.h"
#include "UI/InGameHUD.h"

/**
 * 
 */
class ZIKO_API FillEnergyBar : public FPendingLatentAction
{
	
	AInGameHUD* HUD;

	/*AInGameHUD* HUD;
	float DesiredFillAmount; /*Should be value between 0...1#1#
	float& DT;
	float Elapsed;*/
	
public:
	FillEnergyBar(AInGameHUD* Hud)
	: HUD(Hud) {};

	virtual void UpdateOperation(FLatentResponse& Response) override;
	
};
