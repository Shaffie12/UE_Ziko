// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OverlapBox.h"

#include "DrawDebugHelpers.h"
#include "Actors/IceCrystal.h"
#include "Actors/Projectile.h"
#include "Characters/AI/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"

UOverlapBox::UOverlapBox()
{
	OnComponentBeginOverlap.AddDynamic(this, &UOverlapBox::OnOverlapBegin);
	//OnComponentEndOverlap.AddDynamic(this, &UOverlapBox::OnOverlapEnd);
}

void UOverlapBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* const Owner = GetOwner();
	check(Owner);
	const APawn* const PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	check(PlayerPawn);
	
	if (OtherActor == Owner || OtherActor == PlayerPawn	|| !Owner->ActorHasTag(PlayerWeaponTag)) return;

	ABaseEnemy* const Target = Cast<ABaseEnemy>(OtherActor);
	if (!Target) return;
	
	AProjectile* const Projectile = Cast<AProjectile>(Owner);
	if (Projectile) Projectile->EnemyWasHit(Target);

	AIceCrystal* const Crystal = Cast<AIceCrystal>(Owner);
	if (Crystal) Crystal->EnemyWasHit(Target);
}
