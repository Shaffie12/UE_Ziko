#include "Actors/SwordBasic.h"

#include "Characters/Player/PaladinCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Characters/AI/BaseEnemy.h"

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


void ASwordBasic::ApplyDamageOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if(GetOwner()!=nullptr)
	{
		const APaladinCharacter* Player = Cast<APaladinCharacter>(GetOwner());
		const ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);
		if(Player)
		{
			if(Enemy)
			{
				GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,FString::Printf(TEXT("HIT: %s"),*OtherActor->GetName()));
				UGameplayStatics::ApplyDamage(OtherActor,GetAttackDamage(Player->GetAttackState()),
		GetWorld()->GetFirstPlayerController(),this,UDamageType::StaticClass());
				
			}
			
			
		}
	}
	
}

void ASwordBasic::BaseAttack(){}

void ASwordBasic::FirstAbilityAttack(){}

void ASwordBasic::SecondAbilityAttack()
{
	
}




