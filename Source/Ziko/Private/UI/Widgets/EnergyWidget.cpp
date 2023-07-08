// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EnergyWidget.h"
#include "Characters/Player/BaseCharacter.h"
#include "Components/ProgressBar.h"


void UEnergyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ABaseCharacter* Player = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(Player)
		Player->EnergyLevelChanged.BindUObject(this,&UEnergyWidget::FillBar);
	
}

 void UEnergyWidget::SetFillAmount(float amount) 
{
	EnergyAmountBar->SetPercent(amount);
}

const float& UEnergyWidget::GetFillAmount() const
{
	return EnergyAmountBar->Percent;
}

//coroutine to fill the bar up over time, when an event is called
void UEnergyWidget::FillBar(float amount)
{
	FillEnergyBar* Action = GetWorld()->GetLatentActionManager().FindExistingAction<FillEnergyBar>(this,1);
	if(!Action)
		GetWorld()->GetLatentActionManager().AddNewAction(this,1,
		new FillEnergyBar(1,this,amount,GetWorld()->DeltaTimeSeconds));
}

void UEnergyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

