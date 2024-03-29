// Copyright Euclides Araujo 2018

#include "Tank.h"

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::GetHealthPercent() const
{
	return ( float )CurrentHealth / ( float )StartingHealth;
}

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//MySprungWheel = CreateDefaultSubobject< ASprungWheel>( FName( "Sprung Wheel" ) );
	//Cast< USceneComponent>( MySprungWheel )->SetupAttachment( Cast< USceneComponent>( this->GetParentActor() ) );//Cast< USceneComponent>( Mass ) );

}
float ATank::TakeDamage( float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser )
{
	int32 DamagePoints = FPlatformMath::RoundToInt( DamageAmount );
	int32 DamageToApply = FMath::Clamp( DamagePoints, 0, this->CurrentHealth );

	CurrentHealth -= DamageToApply;
	if( CurrentHealth <= 0 )
	{
		OnDeath.Broadcast();	
	}

	return DamageToApply;
}