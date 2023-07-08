// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/InGameHUD.h"

#include "Characters/Player/BaseCharacter.h"

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
}

void AInGameHUD::UpdateEnergyBar(float amount) const
{
	EnergyWidget->SetFillAmount(amount);
}

