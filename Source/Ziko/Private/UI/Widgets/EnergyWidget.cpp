// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EnergyWidget.h"
#include "Components/ProgressBar.h"


void UEnergyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

 void UEnergyWidget::SetFillAmount(float amount) 
{
	EnergyAmountBar->SetPercent(amount);
}

const float& UEnergyWidget::GetFillAmount() const
{
	return EnergyAmountBar->Percent;
}

void UEnergyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

