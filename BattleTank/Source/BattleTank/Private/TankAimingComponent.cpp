// Copyright Euclides Araujo 2018

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
}

void UTankAimingComponent::Initialise( UTankBarrel * BarrelToSet, UTankTurret * TurretToSet )
{
	Barrel =  BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt( FVector HitLocation )
{
	if( !ensure( Barrel ) ) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation( FName( "Projectile" ) );
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity( this,
																		 OutLaunchVelocity,
																		 StartLocation,
																		 HitLocation,
																		 LaunchSpeed,
																		 false,
																		 0,
																		 0 ,
																		 ESuggestProjVelocityTraceOption::DoNotTrace );
	if( bHaveAimSolution )
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards( AimDirection );
	}
}

void UTankAimingComponent::MoveBarrelTowards( FVector AimDirection )
{
	if( !ensure( Barrel && Turret ) ) { return; }

	// Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate( DeltaRotator.Pitch );
	Turret->Rotate( DeltaRotator.Yaw );
}

void UTankAimingComponent::Fire()
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