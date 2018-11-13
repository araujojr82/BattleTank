// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
 
 // Holds Turret's properties and Rotate method
UCLASS( meta = ( BlueprintSpawnableComponent )) //, hidecategories = ( "Collision" ) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max conter-clockwise speed, and +1 is clockwise
	void Rotate( float RelativeSpeed );

private:
	UPROPERTY( EditAnywhere, Category = Setup )
	float MaxDegreesPerSecond = 25;
};
