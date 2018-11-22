// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise( UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet )
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward( float Throw )
{
	if( !LeftTrack || !RightTrack ) { return; }
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG( LogTemp, Warning, TEXT( "Intend move forward throw: %f" ), Throw )

	LeftTrack->SetThrottle( Throw );
	RightTrack->SetThrottle( Throw );
	// TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight( float Throw )
{
	if( !LeftTrack || !RightTrack ) { return; }
	LeftTrack->SetThrottle( Throw );
	RightTrack->SetThrottle( -Throw );
	// TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove( const FVector & MoveVelocity, bool bForceMaxSpeed )
{
	// No need to call Super as we're replacing the functionality

	auto TankName = this->GetOwner()->GetName();
	UE_LOG( LogTemp, Warning, TEXT( "%s move velocity is %s" ), *TankName, *MoveVelocity.ToString() )
}
