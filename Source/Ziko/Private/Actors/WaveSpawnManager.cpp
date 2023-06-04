// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/WaveSpawnManager.h"
#include "LatentActions/SpawnWave.h"

void AWaveSpawnManager::StartWaves()
{
	GetWorld()->GetLatentActionManager().AddNewAction(this,1,new SpawnWave(7,
		GetWorld()->DeltaTimeSeconds));
}

void AWaveSpawnManager::BeginPlay()
{
	AActor::BeginPlay();
	StartWaves();
}




