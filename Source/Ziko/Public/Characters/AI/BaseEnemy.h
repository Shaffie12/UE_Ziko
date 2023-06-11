// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"
DECLARE_DELEGATE(FOnDestroySignature)
UCLASS()
class ZIKO_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;

	bool IsAlive() const;
	static FOnDestroySignature EnemyDead;
	

private:
	UPROPERTY(EditDefaultsOnly)
	class UHealthComponent* HealthComp;
	
};
