// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "Widgets/EnergyWidget.h"
#include "InGameHUD.generated.h"


/**
 * 
 */
UCLASS()
class ZIKO_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();

	void BeginPlay() override;
	void DrawHUD() override;
	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateEnergyBar(float amount) const;

	UPROPERTY(EditDefaultsOnly,Category="Widgets")
	TSubclassOf<UUserWidget> EnergyWidgetClass;

private:
	UPROPERTY()
	UEnergyWidget* EnergyWidget;
	
};
