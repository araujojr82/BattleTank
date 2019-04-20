// Copyright Euclides Araujo 2018

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>( FName( "Mass-Axle Constraint" ) );
	SetRootComponent( MassAxleConstraint );

	Axle = CreateDefaultSubobject<USphereComponent>( FName( "Axle" ) );
	Axle->SetupAttachment( MassAxleConstraint );

	Wheel = CreateDefaultSubobject<USphereComponent>( FName( "Wheel" ) );
	Wheel->SetupAttachment( Axle );

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>( FName( "Axle-Wheel Constraint" ) );
	AxleWheelConstraint->SetupAttachment( Axle );	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if( !GetAttachParentActor() ) { return; }

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>( GetAttachParentActor()->GetRootComponent() );

	if( !BodyRoot ) { return; }

	MassAxleConstraint->SetConstrainedComponents( BodyRoot, NAME_None, Cast<UPrimitiveComponent>( Axle ), NAME_None );
	AxleWheelConstraint->SetConstrainedComponents( Cast<UPrimitiveComponent>( Axle ), NAME_None, Cast<UPrimitiveComponent>( Wheel ), NAME_None );
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}