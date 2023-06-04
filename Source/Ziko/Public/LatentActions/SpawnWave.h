#pragma once
#include "LatentActions.h"

class SpawnWave : public FPendingLatentAction
{
	float& DT;
	int EnemiesToSpawn;
	int Enemies_Spawned;
	const float WaitTime = 2.0f;
	float Timer;

public:
	SpawnWave(int spawns, float& deltaTime):DT(deltaTime), EnemiesToSpawn(spawns), Enemies_Spawned(0), Timer(0.f){};
	
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
	
	//how to get a list of enemies to choose from?
	void SpawnEnemy()
	{
		UE_LOG(LogTemp,Warning,TEXT("SPAWNED."))
	}
};
