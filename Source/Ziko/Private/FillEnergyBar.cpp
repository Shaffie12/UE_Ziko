// Fill out your copyright notice in the Description page of Project Settings.
#include "Ziko/Public/LatentActions/FillEnergyBar.h"

void FillEnergyBar::UpdateOperation(FLatentResponse& Response)
{
	if(FillWidget)
	{
		if(FillWidget->GetFillAmount()!=DesiredFillAmount)
		{
			Elapsed+=DT;
			if(DesiredFillAmount > FillWidget->GetFillAmount())
				FillWidget->SetFillAmount(FMath::Lerp(FillWidget->GetFillAmount(),DesiredFillAmount,Elapsed/1.0f));
			else
				FillWidget->SetFillAmount(FMath::Lerp(DesiredFillAmount,FillWidget->GetFillAmount(),Elapsed/1.0f));
			
		}
	}
	
	Response.DoneIf(FillWidget->GetFillAmount()==DesiredFillAmount);
		
}



