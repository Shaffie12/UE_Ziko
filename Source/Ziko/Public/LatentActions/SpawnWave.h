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
	
	virtual void UpdateOperation(FLatentResponse& Response) override;
	
	void SpawnEnemy() const;
	
};
