// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/IceCrystal.h"

#include "Characters/AI/BaseEnemy.h"
#include "Components/OverlapBox.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AIceCrystal::AIceCrystal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UOverlapBox>(TEXT("Overlap Box"));
	SetRootComponent(OverlapBox);

	FreezeDamage = 0;
	DamageRate = 0.f;
}

// Called when the game starts or when spawned
void AIceCrystal::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DamageTimer, this, &AIceCrystal::ApplyDamage, DamageRate, true);
}

// Called every frame
void AIceCrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIceCrystal::ApplyDamage()
{
	const FPointDamageEvent PointDamage{};
	for (const auto& Enemy_Speed : FrozenEnemies)
	{
		ABaseEnemy* const Enemy = Enemy_Speed.Key;
		if (!Enemy && !Enemy->IsAlive()) return;

		Enemy->TakeDamage(FreezeDamage, PointDamage, GetInstigatorController(), this);
	}
}

void AIceCrystal::EnemyWasHit(ABaseEnemy* const Enemy)
{
	check(Enemy);
	
	UCharacterMovementComponent* const MovementComp = Enemy->GetCharacterMovement();
	const float WalkSpeed = MovementComp->GetMaxSpeed();
	MovementComp->MaxWalkSpeed = 0.f;
	FrozenEnemies.Add(Enemy, WalkSpeed);
}

void AIceCrystal::DestroyCrystal()
{
	for (const auto& Enemy_Speed : FrozenEnemies)
	{
		const ABaseEnemy* const Enemy = Enemy_Speed.Key;
		if (!Enemy && !Enemy->IsAlive()) return;
		
		const float Speed = Enemy_Speed.Value;
		Enemy->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
	verify(Destroy());
}

