// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeapon.h"
#include "Ziko.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	InteractArea = CreateDefaultSubobject<USphereComponent>(FName("Trigger"));
	InteractArea -> InitSphereRadius(80.0f);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComp);
	
	BaseAttackCost = 0;
	FirstAbilityAttackCost = 0;
	SecondAbilityAttackCost = 0;

	BaseAttackDamage = 0;
	FirstAbilityAttackDamage = 0;
	SecondAbilityAttackDamage = 0;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	InteractArea->SetRelativeLocation(FVector(0,0,MeshComp->Bounds.BoxExtent.Z/2));
	InteractArea -> OnComponentBeginOverlap.AddDynamic(this,&ABaseWeapon::OnOverlapStarted);
	InteractArea -> OnComponentEndOverlap.AddDynamic(this,&ABaseWeapon::OnOverlapEnded);
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
	

uint8 ABaseWeapon::GetAttackCost(const EAttackType AttackType) const
{
	switch (AttackType)
	{
	case EAttackType::AT_Basic: return BaseAttackCost;
	case EAttackType::AT_Ability1: return FirstAbilityAttackCost;
	case EAttackType::AT_Ability2: return SecondAbilityAttackCost;
	default: check(nullptr); return 0; // shouldn't reach this point
	}
}

uint8 ABaseWeapon::GetAttackDamage(const EAttackType AttackType) const
{
	switch (AttackType)
	{
	case EAttackType::AT_Basic: return BaseAttackDamage;
	case EAttackType::AT_Ability1: return FirstAbilityAttackDamage;
	case EAttackType::AT_Ability2: return SecondAbilityAttackDamage;
	default: check(nullptr); return 0; // shouldn't reach this point
	}
}// Fill out your copyright notice in the Description page of Project Settings.

void ABaseWeapon::Interact_Implementation(ABaseCharacter* ItemUser)
{
	if(ItemUser->GetPrimaryWeapon()!= nullptr)
	{
		ItemUser->GetPrimaryWeapon()->Drop(ItemUser);
		Pickup(ItemUser);
	}
	else
		Pickup(ItemUser);
}

void ABaseWeapon::Pickup(ABaseCharacter* ItemUser)
{
	MeshComp -> SetSimulatePhysics(false);
	MeshComp -> SetCollisionProfileName("OverlapAllDynamic");
	MeshComp -> SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractArea -> SetGenerateOverlapEvents(false);
	ItemUser->SetPrimaryWeapon(this);
	
}

void ABaseWeapon::Drop(ABaseCharacter* ItemUser) 
{
	ItemUser->SetPrimaryWeapon(nullptr);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName("Weapons");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InteractArea ->SetGenerateOverlapEvents(true);
	//set the profile back
}



void ABaseWeapon::OnOverlapStarted_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ABaseCharacter>(OtherActor))
	{
		
		Cast<ABaseCharacter>(OtherActor)->AddInteractableActorInRange(this);
		
	}
}

void ABaseWeapon::OnOverlapEnded_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
													UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Cast<ABaseCharacter>(OtherActor))
	{
		Cast<ABaseCharacter>(OtherActor)->RemoveInteractableActorInRange(this);
	}
}







