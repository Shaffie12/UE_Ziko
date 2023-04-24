// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ziko.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABaseWeapon;
class APlayerCharacterController;
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class ZIKO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddInteractableActorInRange(AActor* Item);
	void RemoveInteractableActorInRange(AActor* Item);
	
	bool IsArmed() const { return Weapon != nullptr; }
	bool IsAlive() const { return bIsAlive ;}

	ABaseWeapon* GetPrimaryWeapon() const { return Weapon; }
	void SetPrimaryWeapon(ABaseWeapon* NewWeapon);
	
	void SetAttackState(const EAttackType Type) { AttackType = Type; }
	EAttackType GetAttackState() const { return AttackType; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Perform character base attack*/
	virtual void BaseAttack() PURE_VIRTUAL(ABaseCharacter::BaseAttack, );
	virtual void FirstAbilityAttack() PURE_VIRTUAL(ABaseCharacter::FirstAbilityAttack, );
	virtual void SecondAbilityAttack() PURE_VIRTUAL(ABaseCharacter::SecondAbilityAttack, );
	
private:
	/*Handle character movement*/
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	AActor* GetClosestActorInRange() const;
	/*Interact with closest actor in range*/
	void Interact();
	/*Update character look direction*/
	void UpdateLookDir();
	/*Regenerate player power energy*/
	void RegenerateEnergy(const float DeltaTime);
	
protected:
	/*Abilities Component*/
	UPROPERTY(EditAnywhere, Category = "Ability Components")
	float BaseAttackWaitRate;
	UPROPERTY(EditAnywhere, Category = "Ability Components")
	float MaxEnergy;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Components")
	float EnergyRegenerateRate;
	UPROPERTY(EditAnywhere, Category = "Weapon Compatibility")
	EWeaponType UsableWeaponType = EWeaponType::WP_None;
	
	float EnergyVal;
	EAttackType AttackType;
	bool bIsAlive;

	FTimerHandle AttackTimer;
	
private:
	/*Camera Components*/		
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;

	/*Tag for the weapon attachment socket*/
	UPROPERTY(EditAnywhere, Category = "Tags")
	FName WeaponAttachmentSocketName;
	UPROPERTY(EditAnywhere, Category = "Tags")
	FName PickableItemTag;
	
	
	UPROPERTY()
	ABaseWeapon* Weapon;
	UPROPERTY()
	APlayerCharacterController* PCController;
	/*Set of interactable actors that the player triggered their overlap event*/
	UPROPERTY()
	TSet<AActor*> InteractablesInRange;
	
	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;
};