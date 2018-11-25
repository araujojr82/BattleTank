// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	auto* ControlledTank = Cast<ATank>( GetPawn() );
	if( !ensure( ControlledTank ) ) { return; }

	auto* PlayerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn() );
	if( PlayerTank )
	{

		AActor* PlayerTankActor = Cast<AActor>( PlayerTank );

		// Move towards the player		
		MoveToActor( PlayerTankActor, AcceptanceRadius ); // TODO check radius is in cm

		// Aim towards the player
		ControlledTank->AimAt( PlayerTank->GetActorLocation() );	// is GetTargetLocation() better?		

		// TODO Fire if ready only	
		//ControlledTank->Fire();
	}
}