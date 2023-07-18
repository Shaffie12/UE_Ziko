#include "Actors/SwordBasic.h"

#include "Characters/Player/PaladinCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

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
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,FString::Printf(TEXT("HIT: %s"),*OtherActor->GetName()));
	if(GetOwner()!=nullptr)
	{
		APaladinCharacter* Player =  Cast<APaladinCharacter>(GetOwner());
		if(!Player->AppliedDamage)
		{
			//check if other actor can be damaged
			UGameplayStatics::ApplyDamage(OtherActor,GetAttackDamage(Player->GetAttackState()),
GetWorld()->GetFirstPlayerController(),this,UDamageType::StaticClass());
			Player->AppliedDamage=true;
		}
	}
	
}


void ASwordBasic::BaseAttack(){}

void ASwordBasic::FirstAbilityAttack(){}

void ASwordBasic::SecondAbilityAttack()
{
	
}




