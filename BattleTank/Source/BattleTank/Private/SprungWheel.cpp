// Copyright Euclides Araujo 2018

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PhysicsConstraint = CreateDefaultSubobject< UPhysicsConstraintComponent>( FName( "Physics Constraint" ) );
	SetRootComponent( PhysicsConstraint );

	Mass = CreateDefaultSubobject< UStaticMeshComponent>( FName( "Mass" ) );
	Cast< USceneComponent>( Mass )->SetupAttachment( PhysicsConstraint );

	Wheel = CreateDefaultSubobject< UStaticMeshComponent>( FName( "Wheel" ) );
	Cast<USceneComponent>( Wheel )->SetupAttachment( PhysicsConstraint );
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if( GetAttachParentActor() )
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Null"))
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "Null" ))
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

