// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/MagicWand.h"

#include "Actors/Projectile.h"
#include "Actors/IceCrystal.h"
#include "DrawDebugHelpers.h"
#include "Characters/Player/BaseCharacter.h"
#include "Components/InteractBox.h"

// Sets default values
AMagicWand::AMagicWand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MagicSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Magic Spawn Point"));
	MagicSpawnPoint->SetupAttachment(RootComponent);
	
	IceCrystalDestroyTimer = 0.f;
	//FreezingRange = 0;
	IceCrystalZPos = 0;
}

// Called when the game starts or when spawned
void AMagicWand::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMagicWand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagicWand::BaseAttack()
{
	UWorld* const World = GetWorld();
	check(World);
	ABaseCharacter* const MyOwner = Cast<ABaseCharacter>(GetOwner());
	check(MyOwner);

	FVector const SpawnPoint = MagicSpawnPoint->GetComponentLocation();
	FRotator const SpawnRotation =	FRotator(0.f, MyOwner->GetActorRotation().Yaw, 0.f);

	check(BpProjectile);
	AActor* const MagicBullet = World->SpawnActor(BpProjectile, &SpawnPoint, &SpawnRotation);
	check(MagicBullet);
	
	MagicBullet->SetOwner(this);
	MyOwner->SetAttackState(EAttackType::AT_None);
}

void AMagicWand::FirstAbilityAttack()
{
	UWorld* const World = GetWorld();
	check(World);
	ABaseCharacter* const MyOwner = Cast<ABaseCharacter>(GetOwner());
	check(MyOwner);

	FVector_NetQuantize SpawnPoint;
	const bool bWasHit = MyOwner->GetMouseLocation(SpawnPoint);
	if (!bWasHit) return;

	SpawnPoint.Set(SpawnPoint.X, SpawnPoint.Y, IceCrystalZPos);
	check(BpIceCrystal);
	
	AActor* SpawnedActor = World->SpawnActor(BpIceCrystal, &SpawnPoint);
	check(SpawnedActor);
	SpawnedActor->SetOwner(this);
	
	AIceCrystal* IceCrystal = Cast<AIceCrystal>(SpawnedActor);
	check(IceCrystal);
	
	FTimerHandle DestroyHandle;
	GetWorldTimerManager().SetTimer(DestroyHandle, IceCrystal, &AIceCrystal::DestroyCrystal,IceCrystalDestroyTimer);	
	
	MyOwner->SetAttackState(EAttackType::AT_None);
}

void AMagicWand::SecondAbilityAttack()
{

}

