// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if( !PlayerTank )
	{
		UE_LOG( LogTemp, Warning, TEXT( "AIController can't find player Tank" ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "AIController found player: %s" ), *( PlayerTank->GetName() ) );
	}
}

void ATankAIController::Tick( float DeltaTime )
{
	if( GetPlayerTank() )
	{
		// TODO Move towards the player		
		GetControlledTank()->AimAt( GetPlayerTank()->GetActorLocation() );	// is GetTargetLocation() better?
		// Aim towards the player
		//AimTowardsPlayer();

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if( !PlayerPawn ) { return nullptr; }
	
	return Cast<ATank>(PlayerPawn);
}
