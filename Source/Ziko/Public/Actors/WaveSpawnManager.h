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
	
	const TSubclassOf<ABaseEnemy> GetEnemyType() const
	{
		if(EnemyBPs.Num()> 0)
			return EnemyBPs[0];
		return NULL;
	}
	
	FVector2D GetNextSpawnPos()
	{
		/*float XRand,YRand,R;
		R = FMath::RandRange(0.0f,1.0f);
		XRand =FMath::RandRange(5.0f,15.0f);
		const FVector2D Scrn = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());*/
		
		UE_LOG(LogTemp,Warning,TEXT("asdas"));
		
		return FVector2D(0,0);
	}
};
