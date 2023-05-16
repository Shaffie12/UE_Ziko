#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "BaseWeapon.generated.h"

enum class EAttackType : uint8;

UCLASS()
class ZIKO_API ABaseWeapon : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Pickup(ABaseCharacter* ItemUser);
	void Drop(ABaseCharacter* ItemUser);
	void Interact_Implementation(ABaseCharacter* ItemUser) override;
	
	virtual void BaseAttack() PURE_VIRTUAL(ABaseWeapon::BaseAttack, );
	virtual void FirstAbilityAttack() PURE_VIRTUAL(ABaseWeapon::FirstAbilityAttack, );
	virtual void SecondAbilityAttack() PURE_VIRTUAL(ABaseWeapon::SecondAbilityAttack, );

	UFUNCTION(BlueprintNativeEvent,Category="Overlap")
	void OnOverlapStarted(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent,Category="Overlap")
	void OnOverlapEnded(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/*Send attack energy cost to player*/
	uint8 GetAttackCost(const EAttackType AttackType) const;
	/*Send attack damage to damaged actors*/
	uint8 GetAttackDamage(const EAttackType AttackType) const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* InteractArea;
	
private:
	/*Energy cost of  attacks*/
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 BaseAttackCost;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 FirstAbilityAttackCost;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 SecondAbilityAttackCost;

	/*Damage dealt by attacks*/
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 BaseAttackDamage;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 FirstAbilityAttackDamage;
	UPROPERTY(EditAnywhere, Category = "Ability Attributes")
	uint8 SecondAbilityAttackDamage;
};