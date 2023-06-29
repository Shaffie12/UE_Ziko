#include "Actors/SwordBasic.h"

#include "Characters/Player/PaladinCharacter.h"
#include "Kismet/GameplayStatics.h"

ASwordBasic::ASwordBasic()
{
	
}

void ASwordBasic::BeginPlay()
{
	Super::BeginPlay();
	DamageArea = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));
	DamageArea->OnComponentBeginOverlap.AddDynamic(this,&ASwordBasic::ApplyDamageOnOverlap);
	DamageArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ASwordBasic::Tick(float DeltaSeconds)
{
	
}



void ASwordBasic::BaseAttack()
{
	//probably want to activate the collider when this is called
}

void ASwordBasic::ApplyDamageOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if(GetOwner()!=nullptr)
	{
		APaladinCharacter* Player =  Cast<APaladinCharacter>(GetOwner());
		if(!Player->AppliedDamage)
		{
			UGameplayStatics::ApplyDamage(OtherActor,10.0f,
GetWorld()->GetFirstPlayerController(),this,UDamageType::StaticClass());
			Player->AppliedDamage=true;
		}
	}
	
}

void ASwordBasic::FirstAbilityAttack()
{
	
}

void ASwordBasic::SecondAbilityAttack()
{
	
}




