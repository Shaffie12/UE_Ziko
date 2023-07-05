// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EnergyWidget.h"

#include "Components/ProgressBar.h"


void UEnergyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

 void UEnergyWidget::UpdateDisplayAmount(float amount) const
{
	EnergyAmountBar->SetPercent(amount);
}
