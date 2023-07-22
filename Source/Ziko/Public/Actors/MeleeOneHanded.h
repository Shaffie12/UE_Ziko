#pragma once
#include "BaseWeapon.h"
#include "MeleeOneHanded.generated.h"

class UBoxComponent;
UCLASS()
class ZIKO_API AMeleeOneHanded : public ABaseWeapon
{
	GENERATED_BODY()
public:
	AMeleeOneHanded();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* DamageArea;
	
	
};
