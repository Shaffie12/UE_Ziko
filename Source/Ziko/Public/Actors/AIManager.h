// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/AI/BaseEnemy.h"
#include "AIManager.generated.h"

/**
 * 
 */
UCLASS()
class ZIKO_API AAIManager : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY()
	ABaseEnemy* Self;
	
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* AIBehavior;
	UPROPERTY()
	UBlackboardComponent* BlackBoardComp;

	UPROPERTY(EditAnywhere, Category = "BB Keys")
	FName PlayerPosKey;
	UPROPERTY(EditAnywhere,Category="BB Keys")
	FName AggroKey;
	UPROPERTY(EditAnywhere, Category= "BB Keys")
	FName ImmobileTimerKey;
	UPROPERTY(EditAnywhere,Category="BB Keys")
	FName IsMobileKey;
};

