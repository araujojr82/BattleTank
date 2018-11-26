// Copyright Euclides Araujo 2018

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{	
	Super::BeginPlay(); // Needed for BP Begin Play to run!
}

void ATank::Fire()
{	
	if( !ensure( Barrel ) ) { return; }
	bool isReloaded = ( GetWorld()->GetTimeSeconds() - LastFireTime ) > ReloadTimeInSeconds;

	if( isReloaded )
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG( LogTemp, Warning, TEXT( "%f: Fire!!" ), Time )

		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>( ProjectileBluePrint,
															   Barrel->GetSocketLocation( FName( "Projectile" ) ),
															   Barrel->GetSocketRotation( FName( "Projectile" ) ) );
		Projectile->LauchProjectile( LaunchSpeed );
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}