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
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// So the first fire is after initial reload
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initialise( UTankBarrel * BarrelToSet, UTankTurret * TurretToSet )
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction )
{
	if( RoundsLeft <= 0 )
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if( ( GetWorld()->GetTimeSeconds() - LastFireTime ) < ReloadTimeInSeconds )
	{
		FiringState = EFiringState::Reloading;
	}	
	else if( IsBarrelMoving() )
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if( !ensure( Barrel ) ) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals( AimDirection, 0.01 );	// vectors are equal
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards( AimDirection );
	}
}

void UTankAimingComponent::MoveBarrelTowards( FVector TargetAimDirection )
{
	if( !ensure( Barrel && Turret ) ) { return; }

	// Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = TargetAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate( DeltaRotator.Pitch );

	// Always yaw the shortest way
	if( FMath::Abs( DeltaRotator.Yaw ) < 180 )
	{
		Turret->Rotate( DeltaRotator.Yaw );
	}
	else
	{
		Turret->Rotate( -DeltaRotator.Yaw );		
	}
	
}

void UTankAimingComponent::Fire()
{	
	if( FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming )
	{
		// Spawn a projectile at the socket location on the barrel
		if( !ensure( Barrel ) ) { return; }
		if( !ensure( ProjectileBluePrint ) ) { return; }
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG( LogTemp, Warning, TEXT( "%f: Fire!!" ), Time )

			
		auto Projectile = GetWorld()->SpawnActor<AProjectile>( ProjectileBluePrint,
																Barrel->GetSocketLocation( FName( "Projectile" ) ),
																Barrel->GetSocketRotation( FName( "Projectile" ) ) );
		Projectile->LauchProjectile( LaunchSpeed );
		LastFireTime = GetWorld()->GetTimeSeconds();
		RoundsLeft--;
	}
}