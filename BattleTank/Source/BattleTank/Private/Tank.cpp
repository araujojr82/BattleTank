// Copyright Euclides Araujo 2018

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

//void ATank::BeginPlay()
//{	
//	Super::BeginPlay(); // Needed for BP Begin Play to run!
//}

float ATank::TakeDamage( float DamageAmount, FDamageEvent const &DamageEvent, AController* EventInstigator, AActor* DamageCauser )
{
	int32 DamagePoints = FPlatformMath::RoundToInt( DamageAmount );
	int32 DamageToApply = FMath::Clamp( DamagePoints, 0, this->CurrentHealth );

	CurrentHealth -= DamageToApply;
	if( CurrentHealth <= 0 )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Tank died" ));
	}

	return DamageToApply;
}