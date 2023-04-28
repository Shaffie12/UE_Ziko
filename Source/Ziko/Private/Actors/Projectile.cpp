// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectile.h"

#include "Ziko.h"
#include "Actors/BaseWeapon.h"
#include "Components/OverlapBox.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UOverlapBox>(TEXT("Overlap Box"));
	SetRootComponent(OverlapBox);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Comp"));
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->MaxSpeed = 1000.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::EnemyWasHit(ACharacter* const Enemy)
{
	ABaseWeapon* OwnerWeapon = Cast<ABaseWeapon>(GetOwner());
	check(OwnerWeapon);
	
	const uint8 Damage = OwnerWeapon->GetAttackDamage(EAttackType::AT_Basic);
	const FPointDamageEvent PointDamage{};
	Enemy->TakeDamage(Damage, PointDamage, OwnerWeapon->GetInstigatorController(), OwnerWeapon);
	
	verify(Destroy());
}

