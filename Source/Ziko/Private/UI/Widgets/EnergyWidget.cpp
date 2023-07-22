// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EnergyWidget.h"
#include "Characters/Player/BaseCharacter.h"
#include "Components/ProgressBar.h"


void UEnergyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(Player)
		Player->EnergyLevelChanged.BindUObject(this,&UEnergyWidget::SetFillAmount);
	
}

 void UEnergyWidget::SetFillAmount(float Amount) 
{
		EnergyAmountBar->SetPercent(Amount);
}

const float& UEnergyWidget::GetFillAmount() const
{
	return EnergyAmountBar->Percent;
}

void UEnergyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}

