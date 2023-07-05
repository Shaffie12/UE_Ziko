// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"

AInGameHUD::AInGameHUD()
{
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if(EnergyWidgetClass)
	{
		EnergyWidget = CreateWidget<UEnergyWidget>(GetWorld(),EnergyWidgetClass);
		if(EnergyWidget)
		{
			EnergyWidget->AddToViewport();
		}
	}
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
	
}

void AInGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//we should display the energy as an interpolated amount.
}

void AInGameHUD::UpdateEnergyBar(float amount)
{
	EnergyWidget->UpdateDisplayAmount(amount);
}
