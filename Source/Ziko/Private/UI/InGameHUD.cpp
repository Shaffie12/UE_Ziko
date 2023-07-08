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
		ActiveEnergyFillRoutine = 5;
		GetWorld()->GetLatentActionManager().AddNewAction(this,ActiveEnergyFillRoutine,
			new FillEnergyBar(this));
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

void AInGameHUD::UpdateEnergyBar(float amount) const
{
	EnergyWidget->SetFillAmount(amount);
}

const float& AInGameHUD::GetBarFillAmount() const
{
	return EnergyWidget->GetFillAmount();
}
