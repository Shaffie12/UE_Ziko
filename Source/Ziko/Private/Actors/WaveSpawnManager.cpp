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
	EnemiesAlive = MaxEnemies;
	GetWorld()->GetLatentActionManager().AddNewAction(this,1, new SpawnWave(this,MaxEnemies,GetWorld()->DeltaTimeSeconds));
	ABaseEnemy::EnemyDead.BindUObject(this,&AWaveSpawnManager::DecreaseEnemyCount);
	
}

void AWaveSpawnManager::DecreaseEnemyCount()
{
	EnemiesAlive--;
	if(EnemiesAlive ==0)
	{
		NextWave();
		EnemiesAlive = MaxEnemies;
	}
}

void AWaveSpawnManager::NextWave()
{
	WaveNumber++;
	GetWorld()->GetLatentActionManager().AddNewAction(this,1,new SpawnWave(this,MaxEnemies,
		GetWorld()->DeltaTimeSeconds));
	
}






