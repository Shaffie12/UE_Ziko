// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BaseEnemy.h"

#include "Actors/BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
FOnDestroySignature ABaseEnemy::EnemyDead; 
// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));
	bAggro=false;
	bAttacking=false;
	bWasHit=false;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnHit);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseEnemy::OnDestroy()
{
	PlayAnimMontage(DeathAnimation);
	EnemyDead.Execute();
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
	//what is destroying it?
}

void ABaseEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	const ABaseWeapon* HitByWeapon = Cast<ABaseWeapon>(OtherActor);
	if(HitByWeapon)
	{
		FVector LaunchDirection = OtherActor->GetActorLocation() - GetActorLocation();
		LaunchDirection.Normalize();
		LaunchCharacter(LaunchDirection *-1000.0f,true,true);
	}
	
	
	
}

bool ABaseEnemy::IsAlive() const { return HealthComp->IsAlive(); }

bool ABaseEnemy::IsAttacking() const
{
	return bAttacking;
}

bool ABaseEnemy::IsInAggroRange(const FVector Other) const
{
	return (GetActorLocation() - Other).Size() <= AggroRange;
}

void ABaseEnemy::SetAttacking(bool Value)
{
	bAttacking=Value;
}
