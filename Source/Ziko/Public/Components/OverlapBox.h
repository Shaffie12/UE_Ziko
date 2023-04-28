// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "OverlapBox.generated.h"

/**
 * 
 */
UCLASS()
class ZIKO_API UOverlapBox : public UBoxComponent
{
	GENERATED_BODY()

public:
	UOverlapBox();

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
	FName PlayerWeaponTag;
	UPROPERTY(EditDefaultsOnly)
	FName PlayerTag;
};

