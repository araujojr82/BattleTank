// Copyright Euclides Araujo 2018

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto* ControlledTank = GetPawn();
	if( !ensure( PlayerTank && ControlledTank ) ) { return; }

	// Move towards the player		
	MoveToActor( PlayerTank, AcceptanceRadius ); // TODO check radius is in cm

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if( !ensure( AimingComponent ) ) { return; }
	AimingComponent->AimAt( PlayerTank->GetActorLocation() );	// is GetTargetLocation() better?

	if( AimingComponent->GetFiringState() == EFiringState::Locked )
	{
		AimingComponent->Fire();
	}
}