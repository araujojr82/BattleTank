// Copyright Euclides Araujo 2018

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h" // So we can implement OnDeath

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();	
	if( !ensure( AimingComponent ) ) { return; }	
	FoundAimingComponent( AimingComponent );
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn( APawn* InPawn )
{
	Super::SetPawn( InPawn );
	if( InPawn )
	{
		auto PossessedTank = Cast<ATank>( InPawn );
		if( !ensure( PossessedTank ) ) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic( this, &ATankPlayerController::OnTankDeath );
	}
}

void ATankPlayerController::OnTankDeath()
{
	//UE_LOG( LogTemp, Warning, TEXT( "PlayerController: Received OnDeath broadcast!" ) );
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if( !GetPawn() ) { return; }  // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if( !ensure( AimingComponent ) ) { return; }

	FVector HitLocation; // Out parameter	
	bool bGotHitLocation = GetSightRayHitLocation( HitLocation );
	if( bGotHitLocation )
	{
		AimingComponent->AimAt( HitLocation );
	}
}

// Get world location of linetrace through the crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation ) const
{	
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize( ViewportSizeX, ViewportSizeY );

	FVector2D ScreenLocation = FVector2D( ViewportSizeX * CrossHairXLocation,
										  ViewportSizeY * CrossHairYLocation );

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if( GetLookDirection( ScreenLocation, LookDirection ) )
	{
		// Line-trace along that look direction, and see what we hit ( up to max range )
		return GetLookVectorHitLocation( LookDirection, OutHitLocation );
	}	
	return false;
}

bool ATankPlayerController::GetLookDirection( FVector2D ScreenLocation, FVector& OutLookDirection ) const
{
	FVector CameraWorldLocation;	// To be discarded

	return DeprojectScreenPositionToWorld( ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection );
}

bool ATankPlayerController::GetLookVectorHitLocation( FVector LookDirection, FVector& HitLocation ) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + ( LookDirection * LineTraceRange );
	
	if ( GetWorld()->LineTraceSingleByChannel( HitResult, 
											   StartLocation, 
											   EndLocation, 
											   ECollisionChannel::ECC_Visibility ) )
	{
		// Set Hit Location
		HitLocation = HitResult.Location;
		return true;
	}		
	return false;
}