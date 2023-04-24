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
	//int16 TakeDamage(int16 DamageAmount); //FIXME: use OnTakeAnyDamage delegate
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	uint16 MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	uint16 MaxShield;

	uint16 HealthVal;
	uint16 ShieldVal;
};
