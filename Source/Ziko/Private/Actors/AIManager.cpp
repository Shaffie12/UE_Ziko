// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AIManager.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIManager::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Self = Cast<ABaseEnemy>(InPawn);
	check(Self);
}

void AAIManager::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	check(PlayerPawn);

	check(AIBehavior);
	RunBehaviorTree(AIBehavior);
	
	BlackBoardComp = GetBlackboardComponent();
	check(BlackBoardComp);
}

void AAIManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	check(PlayerPawn);
	const FVector PlayerPos = PlayerPawn->GetActorLocation();
	BlackBoardComp->SetValueAsVector(PlayerPosKey, PlayerPos);
	
	BlackBoardComp->SetValueAsBool(AggroKey,(Self->IsInRange(PlayerPos)));
	

	
}
