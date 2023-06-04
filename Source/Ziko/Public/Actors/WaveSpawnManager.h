// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveSpawnManager.generated.h"
UCLASS()
class ZIKO_API AWaveSpawnManager: public AActor
{
	GENERATED_BODY()
	int WaveNumber = 1;
	int MaxEnemies = WaveNumber * 3;
	void StartWaves();
	virtual void BeginPlay() override;

};
