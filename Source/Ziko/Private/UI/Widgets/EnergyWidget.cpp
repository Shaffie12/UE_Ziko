// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EnergyWidget.h"

#include "Characters/Player/BaseCharacter.h"
#include "Components/ProgressBar.h"


void UEnergyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Ttl= 1.f;
	ABaseCharacter::EnergyTickRateChanged.BindUObject(this,&UEnergyWidget::UpdateTTL);
	CurrentPercent = EnergyAmountBar->Percent;
}

 void UEnergyWidget::UpdateDisplayAmount(float amount) 
{
	CurrentPercent = EnergyAmountBar->Percent;
	NextPercent = amount;
	Elapsed=0.f;
}

void UEnergyWidget::UpdateTTL(float NewTimeSpan)
{
	Ttl = NewTimeSpan;
}

void UEnergyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Elapsed+=InDeltaTime;
	EnergyAmountBar->SetPercent(FMath::Lerp(CurrentPercent,NextPercent,Elapsed/Ttl));
}

