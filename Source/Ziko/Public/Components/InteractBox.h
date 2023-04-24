// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "InteractBox.generated.h"

class UWidgetComponent;
class UInteractWidget;

/**
 * 
 */
UCLASS()
class ZIKO_API UInteractBox : public UBoxComponent
{
	GENERATED_BODY()

public:
	UInteractBox();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractWidget;

	/*WBP_UInteractWidget*/
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractWidget> BpInteractWidget;
};
