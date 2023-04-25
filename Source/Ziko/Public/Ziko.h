// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EAttackType : uint8
{
	AT_None			UMETA(DisplayName = "None"),
	AT_Basic		UMETA(DisplayName = "Basic"),
	AT_Ability1		UMETA(DisplayName = "Ability1"),
	AT_Ability2		UMETA(DisplayName = "Ability2")
};
