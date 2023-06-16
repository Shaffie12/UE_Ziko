#include "Actors/SwordBasic.h"

#include "Kismet/GameplayStatics.h"

ASwordBasic::ASwordBasic()
{
	
}

void ASwordBasic::BeginPlay()
{
	Super::BeginPlay();
	DamageArea->OnComponentBeginOverlap.AddDynamic(this,&ASwordBasic::ApplyDamageOnOverlap);
}


void ASwordBasic::Tick(float DeltaSeconds)
{
	
}


void ASwordBasic::BaseAttack()
{
	
}

void ASwordBasic::ApplyDamageOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor,10.0f,
		GetWorld()->GetFirstPlayerController(),this,UDamageType::StaticClass());
}

void ASwordBasic::FirstAbilityAttack()
{
	
}

void ASwordBasic::SecondAbilityAttack()
{
	
}




