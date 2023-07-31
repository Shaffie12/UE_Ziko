// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SwordHit.generated.h"


/**
 * 
 */
UCLASS()
class ZIKO_API USwordHit : public UAnimNotifyState
{
	GENERATED_BODY()
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
private:
	TArray<AActor*> ToIgnore;
	FHitResult Out;
	
};
