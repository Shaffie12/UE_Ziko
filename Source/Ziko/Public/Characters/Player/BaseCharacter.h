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

DECLARE_DELEGATE_OneParam(FEnergyTickRateChanged,float);
DECLARE_DELEGATE_OneParam(FEnergyLevelChanged,float);

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
	UFUNCTION(BlueprintPure)
	EAttackType GetAttackState() const { return AttackType; }

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Animations")
	UAnimMontage* M_Attack_Basic;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Animations")
	UAnimMontage* M_Attack_First;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Animations")
	UAnimMontage* M_Attack_Second;

	/*Returns true if getting mouse position was successful*/
	bool GetMouseLocation(FVector_NetQuantize& MousePos);

	void SetEnergyRechargeTick(float Value);
	const  float& GetMaxEnergy() const {return MaxEnergy;}
	const float& GetEnergyAmount() const { return EnergyVal;}

	FEnergyTickRateChanged EnergyTickRateChanged;
	FEnergyLevelChanged EnergyLevelChanged;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Perform character base attack*/
	virtual void BaseAttack();
	virtual void FirstAbilityAttack();
	virtual void SecondAbilityAttack();

	UClass* GetInitialWeaponBp() const;
	
private:
	/*Handle character movement*/
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	AActor* GetClosestActorInRange() const;
	/*Interact with closest actor in range*/
	void Interact();
	/*Update character look direction*/
	void UpdateLookDir();
	/*Regenerate player power energy passively*/
	void RegenerateEnergy();

public:
	UPROPERTY()
	bool IsAnimationBusy; // to make sure animation is finished before allowing another attack to be started - set by anim notify
	
protected:
	/*Abilities Component*/
	UPROPERTY(EditAnywhere, Category = "Ability Components")
	float BaseAttackWaitRate;
	UPROPERTY(EditAnywhere, Category = "Ability Components")
	float MaxEnergy;
	UPROPERTY(EditAnywhere,Category = "Ability Components")
	float EnergyRegenerateAmountPerTick;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Components")
	float EnergyRegenerateTick;
	
	float EnergyVal;
	EAttackType AttackType;
	bool bIsAlive;
	FTimerHandle AttackTimer;
	bool CanDoAttack;
	
	
private:
	/*Camera Components*/		
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	USpringArmComponent* CameraSpringComp;
	UPROPERTY(EditAnywhere, Category = "Camera Components")
	UCameraComponent* CameraComp;

	/*Tag for the weapon attachment socket*/
	UPROPERTY(EditAnywhere, Category = "Tags")
	FName WeaponAttachmentSocketName;	//FIXME: WeaponBoneToHide may be referencing same socket
	UPROPERTY()
	ABaseWeapon* Weapon;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseWeapon> StartWeapon;
	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FName WeaponBoneToHide;
	
	UPROPERTY()
	APlayerCharacterController* PCController;
	/*Set of interactable actors that the player triggered their overlap event*/
	UPROPERTY()
	TSet<AActor*> InteractablesInRange;
	/*HitResult used for getting mouse position to UpdateLookDir()*/
	FHitResult OutHit;

	
	
	
};