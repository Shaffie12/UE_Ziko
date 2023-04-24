// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "WizardCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ZIKO_API AWizardCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWizardCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Perform character base attack*/
	virtual void BaseAttack() override;

	/*Perform character base attack*/
	virtual void FirstAbilityAttack() override;

	/*Perform character base attack*/
	virtual void SecondAbilityAttack() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
