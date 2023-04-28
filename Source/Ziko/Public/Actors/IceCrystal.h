// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceCrystal.generated.h"

UCLASS()
class ZIKO_API AIceCrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIceCrystal();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void EnemyWasHit(class ABaseEnemy* const Enemy);
	void DestroyCrystal();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ApplyDamage();
	
private:
	UPROPERTY(EditDefaultsOnly)
	class UOverlapBox* OverlapBox;
	
	UPROPERTY(EditAnywhere)
	uint8 FreezeDamage;
	UPROPERTY(EditAnywhere)
	float DamageRate;
	
	FTimerHandle DamageTimer;
	TMap<ABaseEnemy*, float> FrozenEnemies;
	
};
