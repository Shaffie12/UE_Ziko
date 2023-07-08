// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LatentActions.h"
#include "UI/InGameHUD.h"

/**
 * 
 */
class UEnergyWidget;

class FillEnergyBar : public FPendingLatentAction
{
	int32 Id;
	UEnergyWidget* FillWidget;
	float DesiredFillAmount; /*Should be value between 0...1*/
	float& DT;
	float Elapsed;
	
public:
	FillEnergyBar(int32 UUID, UEnergyWidget* Widget,float DesiredFill, float& DeltaTime)
	: Id(UUID),FillWidget(Widget), DesiredFillAmount(DesiredFill), DT(DeltaTime), Elapsed(0.f){};

	virtual void UpdateOperation(FLatentResponse& Response) override;
	
};
