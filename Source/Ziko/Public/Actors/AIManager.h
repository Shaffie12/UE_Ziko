// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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

private:
	UPROPERTY()
	APawn* PlayerPawn;
	
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* AIBehavior;
	UPROPERTY()
	UBlackboardComponent* BlackBoardComp;

	UPROPERTY(EditAnywhere, Category = "BB Keys")
	FName PlayerPosKey;
};

