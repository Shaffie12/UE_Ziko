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
	virtual void BaseAttack() const override;
	virtual void FirstAbilityAttack() const override;
	virtual void SecondAbilityAttack() const override;
	
private:
	/*Spawn point for magic to attack*/
	UPROPERTY(EditAnywhere)
	USceneComponent* MagicSpawnPoint;

	/*Default actor to spawn when performing any attack*/
	UPROPERTY(EditDefaultsOnly, Category = "Ability Attributes")
	TSubclassOf<AActor> BpMagicBullet;
};
