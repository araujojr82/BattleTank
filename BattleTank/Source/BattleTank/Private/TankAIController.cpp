// Copyright Euclides Araujo 2018

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h" // So we can implement OnDeath
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn( APawn* InPawn )
{
	Super::SetPawn( InPawn );
	if( InPawn )
	{
		auto PossessedTank = Cast<ATank>( InPawn );
		if( !ensure( PossessedTank ) ) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic( this, &ATankAIController::OnTankDeath );
	}
}

void ATankAIController::OnTankDeath()
{
	if( !GetPawn() ) { return; }

	//UE_LOG( LogTemp, Warning, TEXT( "AIController: Received OnDeath broadcast!" ) );
	GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto* ControlledTank = GetPawn();
	if( !ensure( ControlledTank ) ) { return; }

	if( !PlayerTank ) { return; }

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