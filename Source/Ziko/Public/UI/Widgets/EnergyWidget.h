// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnergyWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZIKO_API UEnergyWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
public:
	virtual void NativeConstruct() override;
	void SetFillAmount(float amount);
	const float& GetFillAmount() const;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget))
	class UProgressBar* EnergyAmountBar;
	
	
	
};
