// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Components/InteractBox.h"
#include "GameFramework/Actor.h"
#include "MagicWand.generated.h"

UCLASS()
class ZIKO_API AMagicWand : public ABaseWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicWand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Perform Wand Attacks*/
	virtual void BaseAttack() override;
	virtual void FirstAbilityAttack() override;
	virtual void SecondAbilityAttack() override;
	
private:
	/*Spawn point for magic for projectile attacks*/
	UPROPERTY(EditAnywhere)
	USceneComponent* MagicSpawnPoint;

	/*Base ability attack attributes*/
	UPROPERTY(EditDefaultsOnly, Category = "Base Attack")
	TSubclassOf<class AProjectile> BpProjectile;
	
	/*First ability attack attributes*/
	UPROPERTY(EditDefaultsOnly, Category = "First Ability Attack")
	TSubclassOf<class AIceCrystal> BpIceCrystal;
	UPROPERTY(EditAnywhere, Category = "First Ability Attack")
	float IceCrystalDestroyTimer;
	//UPROPERTY(EditAnywhere, Category = "First Ability Attack")
	//uint8 FreezingRange;
	UPROPERTY(EditAnywhere, Category = "First Ability Attack")
	uint8 IceCrystalZPos;
	
};