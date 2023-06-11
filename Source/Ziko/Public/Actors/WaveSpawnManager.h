// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/BaseEnemy.h"
#include "WaveSpawnManager.generated.h"

UCLASS()
class ZIKO_API AWaveSpawnManager: public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,NoClear, Category = "Spawn")
	TArray<TSubclassOf<ABaseEnemy>> EnemyBPs;
	int WaveNumber = 1; //need a way to get a ref to this
	int MaxEnemies = WaveNumber * 3;
	int EnemiesAlive = 0;
	void NextWave();
	virtual void BeginPlay() override;
	void DecreaseEnemyCount(); 
public:
	TSubclassOf<ABaseEnemy> GetEnemyType() const;
	FVector GetNextSpawnPos() const;
};
