// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BaseEnemy.h"

#include "Components/HealthComponent.h"
FOnDestroySignature ABaseEnemy::EnemyDead; 
// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseEnemy::OnDestroy()
{
	EnemyDead.Execute();
	UE_LOG(LogTemp,Warning,TEXT("ENEMY KILLED."))
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	check(HealthComp);
	const uint16 Health = HealthComp->TakeDamage(Damage);
	UE_LOG(LogTemp, Warning, TEXT("Health left: %d"), Health);

	if (Health == 0)
	{
		DetachFromControllerPendingDestroy();
		OnDestroy();
		verify(Destroy() == true);
	}
	return Damage;
}

bool ABaseEnemy::IsAlive() const { return HealthComp->IsAlive(); }
