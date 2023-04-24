// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class ZIKO_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Use UInteractWidget(FText&& InteractText) instead! Need to initialize displayed text
	//Only provided as UObject system requires default ctor.
	// UInteractWidget();
	//
	// explicit UInteractWidget(FName&& InteractText);
	
private:
	//Display text
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* InteractTxtBlock;
};
