// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ziko/Public/LatentActions/FillEnergyBar.h"
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

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateEnergyBar(float amount) const;
	UFUNCTION()
	const float& GetBarFillAmount() const;
	UFUNCTION()
	int32 GetActiveFillRoutineId() const {return ActiveEnergyFillRoutine;}

	UPROPERTY(EditDefaultsOnly,Category="Widgets")
	TSubclassOf<UUserWidget> EnergyWidgetClass;

private:
	UPROPERTY()
	UEnergyWidget* EnergyWidget;
	
	int32 ActiveEnergyFillRoutine;
	
};
