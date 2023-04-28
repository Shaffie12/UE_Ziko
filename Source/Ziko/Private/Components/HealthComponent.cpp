// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	HealthVal = 0;
	ShieldVal = 0;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthVal = MaxHealth;
	ShieldVal = MaxShield;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

uint16 UHealthComponent::TakeDamage(uint16 DamageAmount)
{
	uint16 DamageApplied = FMath::Min(ShieldVal, DamageAmount);
	ShieldVal -= DamageApplied;
	
	if (DamageApplied == DamageAmount) return HealthVal;

	DamageApplied = DamageAmount - DamageApplied;
	HealthVal -= FMath::Min(HealthVal, DamageApplied);
	
	return HealthVal;
}

