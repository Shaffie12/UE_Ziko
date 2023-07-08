// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/EnergyWidget.h"
#include "InGameHUD.generated.h"

class UEnergyWidget;

UCLASS()
class AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();
	
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateEnergyBar(float amount) const;
	
	
	UPROPERTY(EditDefaultsOnly,Category="Widgets")
	TSubclassOf<UUserWidget> EnergyWidgetClass;

private:
	UPROPERTY()
	UEnergyWidget* EnergyWidget;
	
	
};
