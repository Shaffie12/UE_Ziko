// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/BaseCharacter.h"

#include "DrawDebugHelpers.h"
#include "NetworkMessage.h"
#include "Actors/MagicWand.h"
#include "Actors/PlayerCharacterController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/MeleeOneHanded.h"
#include "Characters/CharacterAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CanDoAttack = true;
	
	CameraSpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring"));
	CameraSpringComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(CameraSpringComp);

	CameraSpringComp->TargetArmLength = 750.f;
	CameraSpringComp->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));

	MaxEnergy = -1.f;
	EnergyRegenerateRate = -1.f;
	EnergyVal = -1.f;

	AttackType = EAttackType::AT_None;

	Weapon = nullptr;
	PCController = nullptr;
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnergyVal = MaxEnergy;
	PCController = Cast<APlayerCharacterController>(GetController());
	check(PCController);

	USkeletalMeshComponent* const PlayerMesh = GetMesh();
	check(PlayerMesh);
	PlayerMesh->HideBoneByName(WeaponBoneToHide, EPhysBodyOp::PBO_None);
	
	Weapon = GetWorld()->SpawnActor<ABaseWeapon>(StartWeapon);
	check(Weapon);
	Weapon->Pickup(this);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLookDir();
	RegenerateEnergy(DeltaTime); //FIXME: Don't regenerate in Tick, use Timer mayb
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("BaseAttack"), EInputEvent::IE_Pressed, this, &ABaseCharacter::BaseAttack);
	PlayerInputComponent->BindAction(TEXT("Ability1"), EInputEvent::IE_Pressed, this, &ABaseCharacter::FirstAbilityAttack);
	PlayerInputComponent->BindAction(TEXT("Ability2"), EInputEvent::IE_Pressed, this, &ABaseCharacter::SecondAbilityAttack);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Interact);
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(FVector::ForwardVector, AxisValue);
	
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(FVector::RightVector, AxisValue);
}

void ABaseCharacter::UpdateLookDir()
{
	if (!PCController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit)) return;
	const FVector PlayerFwd = GetActorLocation() + GetActorForwardVector();
	
	const FRotator NewRot = ( OutHit.Location - PlayerFwd ).Rotation();;
	GetController()->SetControlRotation((FRotator(0.0f,NewRot.Yaw,0.0f)));
	DrawDebugSphere(GetWorld(),OutHit.Location,100,12,FColor::Green);
}

void ABaseCharacter::AddInteractableActorInRange(AActor* Item)
{
	InteractablesInRange.Add(Item);
}

void ABaseCharacter::RemoveInteractableActorInRange(AActor* Item)
{
	InteractablesInRange.Remove(Item);
}

void ABaseCharacter::Interact()
{
	if (InteractablesInRange.Num() == 0) return;	//FIXME: Couldn't find TArray::IsEmpty()??

	AActor* Item = GetClosestActorInRange();	
	check(Item);
	
	if (Item->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_Interact(Item,this);
	}
	InteractablesInRange.Remove(Item);
}

void ABaseCharacter::SetPrimaryWeapon(ABaseWeapon* NewWeapon)
{
	if(!NewWeapon) return;
	
	Weapon=NewWeapon;
	Weapon->SetActorLocation(FVector(0.f));
	Weapon->AttachToComponent(GetMesh() ,FAttachmentTransformRules::KeepRelativeTransform,WeaponBoneToHide);
	Weapon->SetOwner(this);
}

AActor* ABaseCharacter::GetClosestActorInRange() const
{
	const FVector PlayerFwd = GetActorForwardVector();
	AActor* ClosestActor = nullptr;
	float AngleInRad = 3.14f;	// initialize with ~180 deg
	
	for (AActor* const Item : InteractablesInRange)
	{
		const FVector PlayerToItem = Item->GetActorLocation() - GetActorLocation();
		const float CosAngle = FVector::DotProduct(PlayerFwd, PlayerToItem) / (PlayerFwd.Size() * PlayerToItem.Size());
		const float Angle = FMath::Acos(CosAngle);
		
		if (Angle <= AngleInRad)
		{
			AngleInRad = Angle;
			ClosestActor = Item;
		}
	}
	
	check(ClosestActor);
	return ClosestActor;
}

void ABaseCharacter::BaseAttack()
{
	if(!IsArmed())return;
	const ABaseWeapon* const HeldWeapon = GetPrimaryWeapon();
	const int8 AttackEnergyCost = HeldWeapon->GetAttackCost(EAttackType::AT_Basic);
	if (EnergyVal < AttackEnergyCost)
	{
		CanDoAttack = false;
		return;
	}
	CanDoAttack=true;
	EnergyVal -= AttackEnergyCost;
	GetWorld()->GetTimerManager().PauseTimer(EnergyTickHandle);
	EnergyLevelChanged.Execute(EnergyVal/MaxEnergy,false);
	//GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Magenta,FString::Printf(TEXT("ENERGY: %f"),EnergyVal));
}

void ABaseCharacter::FirstAbilityAttack()
{
	if(!IsArmed())return;
	const ABaseWeapon* const HeldWeapon = GetPrimaryWeapon();
	const int8 AttackEnergyCost = HeldWeapon->GetAttackCost(EAttackType::AT_Basic);
	if (EnergyVal < AttackEnergyCost) return;
	EnergyVal -= AttackEnergyCost;
	
	
	
}

void ABaseCharacter::SecondAbilityAttack()
{
	if(!IsArmed()) return;
	
	const ABaseWeapon* const HeldWeapon = GetPrimaryWeapon();
	const int8 AttackEnergyCost = HeldWeapon->GetAttackCost(EAttackType::AT_Basic);
	if (EnergyVal < AttackEnergyCost) return;
	EnergyVal -= AttackEnergyCost;
}

inline void ABaseCharacter::RegenerateEnergy(const float DeltaTime)
{
	EnergyVal = FMath::Clamp(EnergyVal + EnergyRegenerateAmountPerTick, 0.f, MaxEnergy);
	EnergyLevelChanged.Execute(EnergyVal/MaxEnergy,true);
	
}

bool ABaseCharacter::GetMouseLocation(FVector_NetQuantize& MousePos)
{
	check(PCController);
	if (!PCController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit))
		return false;

	MousePos = OutHit.ImpactPoint;
	OutHit.Reset();
	return true;
}

UClass* ABaseCharacter::GetInitialWeaponBp() const
{
	return StartWeapon;
}
