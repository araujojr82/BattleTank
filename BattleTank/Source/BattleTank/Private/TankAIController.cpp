// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	auto* ControlledTank = Cast<ATank>( GetPawn() );
	if( !ControlledTank ) { return; }

	auto* PlayerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn() );
	if( PlayerTank )
	{
		// TODO Move towards the player		

		// Aim towards the player
		ControlledTank->AimAt( PlayerTank->GetActorLocation() );	// is GetTargetLocation() better?		

		// TODO Fire if ready only	
		ControlledTank->Fire();
	}
}