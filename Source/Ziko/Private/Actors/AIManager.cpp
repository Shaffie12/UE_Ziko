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
	BlackBoardComp->SetValueAsVector(PlayerPosKey, PlayerPawn->GetActorLocation());
	
	const bool InAggroRange = (Self->GetActorLocation() - PlayerPawn->GetActorLocation()).Size() <= 15.0f;
	BlackBoardComp->SetValueAsBool(AggroKey,InAggroRange);
	Self->SetAggro(InAggroRange);
	

	
}
