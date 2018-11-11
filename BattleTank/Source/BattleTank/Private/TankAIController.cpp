// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG( LogTemp, Warning, TEXT( "PlayerController Begin Play" ) );

	//auto ControlledTank = GetControlledTank();

	//if( !ControlledTank )
	//{
	//	UE_LOG( LogTemp, Warning, TEXT( "AIController not possesing a tank" ) );
	//}
	//else
	//{
	//	UE_LOG( LogTemp, Warning, TEXT( "AIController possesing: %s" ), *( ControlledTank->GetName() ) );

	//}

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

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

ATank * ATankAIController::GetPlayerTank() const
{
	// This is my solution and it works as well...
	//ATank* PlayerTank = nullptr;
	//ATankPlayerController* PlayerController;
	//PlayerController = Cast<ATankPlayerController>( GetWorld()->GetFirstPlayerController() );
	//PlayerTank = Cast<ATank>( PlayerController->GetControlledTank() );
	//return PlayerTank;

	auto* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if( !PlayerPawn ) { return nullptr; }
	
	return Cast<ATank>(PlayerPawn);
}
