#include "Ziko/Public/LatentActions/SpawnWave.h"

void SpawnWave::UpdateOperation(FLatentResponse& Response)
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

void SpawnWave::SpawnEnemy() const
{
	UWorld* World = Mgr->GetWorld();
	if(World)
	{
		const TSubclassOf<ABaseEnemy> Spawn = Mgr->GetEnemyType();
		if(Spawn!=NULL)
			World->SpawnActor<ABaseEnemy>(Mgr->GetEnemyType(),Mgr->GetNextSpawnPos(),FRotator::ZeroRotator);
	}
}
