#pragma once

#include "MeleeOneHanded.h"
#include "Components/BoxComponent.h"
#include "Swordbasic.generated.h"

UCLASS()
class ZIKO_API ASwordBasic : public AMeleeOneHanded
{
	GENERATED_BODY()
	
public:
	ASwordBasic();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BaseAttack() override;
	UFUNCTION()
	void ApplyDamageOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
	virtual void FirstAbilityAttack() override;
	virtual void SecondAbilityAttack() override;

};
