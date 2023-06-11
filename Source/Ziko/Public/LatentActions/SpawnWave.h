#pragma once
#include "LatentActions.h"
#include "Actors/WaveSpawnManager.h"

class SpawnWave : public FPendingLatentAction
{
	AWaveSpawnManager* Mgr;
	float& DT;
	int EnemiesToSpawn;
	int Enemies_Spawned;
	const float WaitTime = 2.0f;
	float Timer;

public:
	SpawnWave(AWaveSpawnManager* Mgr, int& spawns, float& deltaTime): Mgr(Mgr),DT(deltaTime), EnemiesToSpawn(spawns), Enemies_Spawned(0), Timer(0.f){};
	
	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		if(Timer<=0)
		{
			SpawnEnemy();
			Enemies_Spawned++;
			Timer = FMath::RandRange(1,5);
		}
		else
			Timer-=DT;
		
		Response.DoneIf(Enemies_Spawned == EnemiesToSpawn);
	}
	
	void SpawnEnemy()
	{
		UWorld* world = Mgr->GetWorld();
		if(world)
		{
			TSubclassOf<ABaseEnemy> Spawn = Mgr->GetEnemyType();
			if(Spawn!=NULL)
				world->SpawnActor<ABaseEnemy>(Mgr->GetEnemyType(),FVector::ZeroVector,FRotator::ZeroRotator);
		}
		
	}
	
};
