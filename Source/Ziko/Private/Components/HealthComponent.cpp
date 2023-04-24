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

// int16 UHealthComponent::TakeDamage(int16 DamageAmount)
// {
// 	int16 Damage = FMath::Min(ShieldVal, DamageAmount);
// 	ShieldVal -= Damage;
// 	
// 	if (Damage == DamageAmount) return HealthVal;
//
// 	Damage = DamageAmount - Damage;
// 	HealthVal -= FMath::Min(HealthVal, Damage);
// 	
// 	return HealthVal;
// }

