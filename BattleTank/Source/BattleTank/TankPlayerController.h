// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;	
	
	virtual void Tick( float DeltaTime ) override;

private:
	ATank* GetControlledTank() const;

	// Start the tank moving the barrel so that the shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation( FVector& OutHitLocation ) const;

	bool GetLookDirection( FVector2D ScreenLocation, FVector& OutHitLocation ) const;

	bool GetLookVectorHitLocation( FVector LookDirection, FVector& HitLocation ) const;

	UPROPERTY( EditAnywhere )
	float CrossHairXLocation = 0.5;

	UPROPERTY( EditAnywhere )
	float CrossHairYLocation = 0.3333;

	UPROPERTY( EditAnywhere )
	float LineTraceRange = 1000000.0f;

};