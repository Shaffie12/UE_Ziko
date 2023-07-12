#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "LatentActions/CompileDamage.h"
#include "PaladinCharacter.generated.h"

UCLASS()
class ZIKO_API APaladinCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	UParticleSystemComponent * Aura;
	bool Channelling;
	

public:
	APaladinCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void BaseAttack() override;

	/*Perform character base attack*/
	virtual void FirstAbilityAttack() override;

	/*Perform character base attack*/
	virtual void SecondAbilityAttack() override;

public:
	UPROPERTY()
	bool IsBusy;
	UPROPERTY()
	bool AppliedDamage;
	
};
