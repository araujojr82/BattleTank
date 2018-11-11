// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG( LogTemp, Warning, TEXT( "PlayerController Begin Play" ) );

	auto ControlledTank = GetControlledTank();

	if( !ControlledTank )
	{
		UE_LOG( LogTemp, Warning, TEXT( "AIController not possesing a tank" ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "AIController possesing: %s" ), *( ControlledTank->GetName() ) );

	}

}