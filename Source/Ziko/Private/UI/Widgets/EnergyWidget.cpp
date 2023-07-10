// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/EnergyWidget.h"
#include "Characters/Player/BaseCharacter.h"
#include "Components/ProgressBar.h"


void UEnergyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DesiredFill=0.f;
	Filling=true;
	Player = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(Player)
		Player->EnergyLevelChanged.BindUObject(this,&UEnergyWidget::SetFillAmount);
	
}

 void UEnergyWidget::SetFillAmount(float Amount, bool Regen) 
{
	Filling = Regen;
	CurrentFill = EnergyAmountBar->Percent;
	DesiredFill = Amount;
	Elapsed=0.f;
	if(!Regen)
	{
		EnergyAmountBar->SetPercent(Amount);
		GetWorld()->GetTimerManager().UnPauseTimer(Player->EnergyTickHandle);
	}
		
	//we have to make sure the timer pauses when this happens
}

const float& UEnergyWidget::GetFillAmount() const
{
	return EnergyAmountBar->Percent;
}

void UEnergyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(EnergyAmountBar->Percent!=1.0f && Filling)
	{
		Elapsed+=InDeltaTime;
		EnergyAmountBar->SetPercent( FMath::Lerp(CurrentFill,DesiredFill,Elapsed/1.0f));
		
	}
	
}

