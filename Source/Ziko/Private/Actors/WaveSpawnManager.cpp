// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/WaveSpawnManager.h"
#include "LatentActions/SpawnWave.h" 

AWaveSpawnManager::AWaveSpawnManager()
{
	ABaseEnemy::EnemyDead.BindUObject(this,&AWaveSpawnManager::DecreaseEnemyCount);
}

void AWaveSpawnManager::BeginPlay()
{
	AActor::BeginPlay();
	TArray<TSubclassOf<ABaseEnemy>> List = EnemyBPs;
	EnemiesAlive = MaxEnemies;
	GetWorld()->GetLatentActionManager().AddNewAction(this,1, new SpawnWave(this,MaxEnemies,GetWorld()->DeltaTimeSeconds));
}

//game will crash when this is called if the enemy was not spawned by the manager
void AWaveSpawnManager::DecreaseEnemyCount()
{
	EnemiesAlive--;
	if(EnemiesAlive ==0)
	{
		NextWave();
		EnemiesAlive = MaxEnemies;
	}
}


TSubclassOf<ABaseEnemy> AWaveSpawnManager::GetEnemyType() const
{
	if(EnemyBPs.Num()> 0)
		return EnemyBPs[0];
	return NULL;
}

FVector AWaveSpawnManager::GetNextSpawnPos() const
{
	const FVector2D Scrn = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	float XRand,YRand,R;
	R = FMath::RandRange(0.0f,1.0f);
	XRand = FMath::RandRange(10.0f,30.0f);
	YRand = FMath::RandRange(10.0f,30.0f);

	XRand =  R > 0.5f ? Scrn.X + XRand : -Scrn.X -XRand;
	R = FMath::RandRange(0.0f,1.0f);
	YRand = R > 0.5f? -Scrn.Y + YRand : -Scrn.Y- YRand;
		
	return FVector(XRand,YRand,0.0f);
}

void AWaveSpawnManager::NextWave()
{
	WaveNumber++;
	MaxEnemies = WaveNumber * 3;
	GetWorld()->GetLatentActionManager().AddNewAction(this,1,new SpawnWave(this,MaxEnemies,
		GetWorld()->DeltaTimeSeconds));
	
}






