// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractBox.h"

#include "Characters/Player/BaseCharacter.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/InteractWidget.h"

UInteractBox::UInteractBox()
{
	// Register overlap events
	OnComponentBeginOverlap.AddDynamic(this, &UInteractBox::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractBox::OnOverlapEnd);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interact Widget"));
	InteractWidget->SetupAttachment(this);
	InteractWidget->SetVisibility(false);
	InteractWidget->SetRelativeLocation(FVector(0.f));
	InteractWidget->SetRelativeRotation(FRotator(0.f));
}

void UInteractBox::BeginPlay()
{
	Super::BeginPlay();

	check(InteractWidget);
	check(BpInteractWidget);
	InteractWidget->SetWidgetClass(BpInteractWidget);
}

void UInteractBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Owner is the actor this box is attached to.
	AActor* Owner = GetOwner();
	if (Owner && OtherActor && OtherActor != Owner)
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);
		if (!Character) return;
		
		Character->AddInteractableActorInRange(Owner);
		check(InteractWidget);
		InteractWidget->SetVisibility(true);
	}
}

void UInteractBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	// Owner is the actor this box is attached to.
	AActor* Owner = GetOwner();
	if (Owner && OtherActor && OtherActor != Owner)
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);
		if (!Character) return;
		
		Character->RemoveInteractableActorInRange(Owner);
		check(InteractWidget);
		InteractWidget->SetVisibility(false);
	}
}


