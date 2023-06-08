// Copyright Epic Games, Inc. All Rights Reserved.


#include "Ziko/Public/GameModes/ZikoGameModeBase.h"

void AZikoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	const FActorSpawnParameters Params;
	GetWorld()->SpawnActor<AWaveSpawnManager>(FVector::ZeroVector,FRotator::ZeroRotator,Params);
	
}	
