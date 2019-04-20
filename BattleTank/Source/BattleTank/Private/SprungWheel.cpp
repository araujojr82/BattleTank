// Copyright Euclides Araujo 2018

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mass = CreateDefaultSubobject< UStaticMeshComponent>( FName( "Mass" ) );
	SetRootComponent( Cast<USceneComponent>( Mass ) );	

	PhysicsConstraint = CreateDefaultSubobject< UPhysicsConstraintComponent>( FName( "Physics Constraint" ) );	
	PhysicsConstraint->SetupAttachment( Cast< USceneComponent>( Mass ) );
	//PhysicsConstraint->AttachToComponent( Cast< USceneComponent>( Mass ), FAttachmentTransformRules::KeepRelativeTransform );

	Wheel = CreateDefaultSubobject< UStaticMeshComponent>( FName( "Wheel" ) );
	Cast<USceneComponent>( Wheel )->SetupAttachment( Cast< USceneComponent>( Mass ) );
	//Cast<USceneComponent>( Wheel )->AttachToComponent( Cast< USceneComponent>( Mass ), FAttachmentTransformRules::KeepRelativeTransform );
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

