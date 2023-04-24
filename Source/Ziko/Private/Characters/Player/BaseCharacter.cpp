// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/BaseCharacter.h"

#include "DrawDebugHelpers.h"
#include "NetworkMessage.h"
#include "Actors/MagicWand.h"
#include "Actors/PlayerCharacterController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/MeleeOneHanded.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
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
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLookDir();
	RegenerateEnergy(DeltaTime); //FIXME: Don't regenerate in Tick, use Timer maybe
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
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ABaseCharacter::UpdateLookDir()
{
	if (!PCController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit)) return;
	const FVector player_fwd = GetActorLocation() + GetActorForwardVector();
	
	FRotator newRot = ( OutHit.Location - player_fwd ).Rotation();
	AddActorLocalRotation(FRotator(0.0f,newRot.Yaw,0.0f));
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

	AActor* Item = GetClosestActorInRange();	//FIXME: Get closest item based on distance and player look direction
	
	check(Item);
	if (Item->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_Interact(Item,this);
	}

	InteractablesInRange.Remove(Item);
}

void ABaseCharacter::SetPrimaryWeapon(ABaseWeapon* NewWeapon)
{
	if(NewWeapon != nullptr)
	{
		Weapon=NewWeapon;
		Weapon->SetActorLocation(FVector(0.f));
		Weapon->AttachToComponent(GetMesh() ,FAttachmentTransformRules::SnapToTargetIncludingScale,WeaponAttachmentSocketName);
		Weapon->SetOwner(this);
	}
	else Weapon = nullptr;
	
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

void ABaseCharacter::RegenerateEnergy(const float DeltaTime)
{
	EnergyVal = FMath::Clamp(EnergyVal + (EnergyRegenerateRate * DeltaTime), 0.f, MaxEnergy);
}