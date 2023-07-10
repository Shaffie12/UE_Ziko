// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Player/BaseCharacter.h"
#include "EnergyWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZIKO_API UEnergyWidget : public UUserWidget
{
	GENERATED_BODY()


	void FillBar(float amount);
	float DesiredFill;
	float CurrentFill;
	float Elapsed;
	bool Filling;
	UPROPERTY()
	ABaseCharacter* Player;
	
protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
public:
	virtual void NativeConstruct() override;
	void SetFillAmount(float Amount,bool Regen);
	const float& GetFillAmount() const;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget))
	class UProgressBar* EnergyAmountBar;
	
};
