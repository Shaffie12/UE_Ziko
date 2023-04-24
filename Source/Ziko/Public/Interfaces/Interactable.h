#pragma once

#include "CoreMinimal.h"
#include "Characters/Player/BaseCharacter.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(Blueprintable)
class ZIKO_API UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ZIKO_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Interact")
	void Interact(ABaseCharacter* ItemUser);

	UFUNCTION(BlueprintNativeEvent, Category="Overlap")
	void EnteredInteractionZone(AActor* ItemUser);

	UFUNCTION(BlueprintNativeEvent, Category="Overlap")
	void LeftInteractionZone(AActor* ItemUser);
};
