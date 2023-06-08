// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/WaveSpawnManager.h"
#include "LatentActions/SpawnWave.h" 

/**
 * need a delegate to check when all enemies are killed.
 */
void AWaveSpawnManager::BeginPlay()
{
	AActor::BeginPlay();
	TArray<TSubclassOf<ABaseEnemy>> List = EnemyBPs;
	GetWorld()->GetLatentActionManager().AddNewAction(this,1, new SpawnWave(*this,MaxEnemies,GetWorld()->DeltaTimeSeconds));
}

void AWaveSpawnManager::NextWave()
{
	WaveNumber++;
	GetWorld()->GetLatentActionManager().AddNewAction(this,1,new SpawnWave(*this,MaxEnemies,
		GetWorld()->DeltaTimeSeconds));
	
}






