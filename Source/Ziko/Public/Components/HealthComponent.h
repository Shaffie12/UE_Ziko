// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZIKO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	uint16 TakeDamage(uint16 DamageAmount);

	bool IsAlive() const { return ShieldVal == 0 && HealthVal == 0; }
	
private:
	uint16 HealthVal;
	uint16 ShieldVal;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	uint16 MaxHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	uint16 MaxShield;
};
