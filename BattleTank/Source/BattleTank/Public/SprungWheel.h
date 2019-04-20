// Copyright Euclides Araujo 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstraint();

	// Components
	UPROPERTY( VisibleAnywhere, Category = "Components" )
	UPhysicsConstraintComponent* MassAxleConstraint = nullptr;	

	UPROPERTY( VisibleAnywhere, Category = "Components" )
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	UPROPERTY( VisibleAnywhere, Category = "Components" )
	USphereComponent* Axle = nullptr;

	UPROPERTY( VisibleAnywhere, Category = "Components" )
	USphereComponent* Wheel = nullptr;
};
