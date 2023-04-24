#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "PaladinCharacter.generated.h"

UCLASS()
class ZIKO_API APaladinCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Animations")
	UAnimMontage* M_Attack_Basic;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Animations")
	UAnimMontage* M_Attack_First;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Animations")
	UAnimMontage* M_Attack_Second;
	
	APaladinCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void BaseAttack() override;

	/*Perform character base attack*/
	virtual void FirstAbilityAttack() override;

	/*Perform character base attack*/
	virtual void SecondAbilityAttack() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
};
