// Copyright Euclides Araujo 2018

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if( ensure( AimingComponent ) )
	{
		FoundAimingComponent( AimingComponent );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Player controller can't find aiming component at Begin Play" ) )
	}
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if( !ensure( GetControlledTank() ) ) { return; }

	FVector HitLocation; // Out parameter	

	if( GetSightRayHitLocation( HitLocation ) )
	{
		GetControlledTank()->AimAt( HitLocation );
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
		if( GetLookVectorHitLocation( LookDirection, OutHitLocation ) )
		{
			return true;
		}		
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