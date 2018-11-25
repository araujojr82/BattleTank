// Copyright Euclides Araujo 2018

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION( BlueprintCallable, Category = "Setup" )
	void Initialise( UTankBarrel* BarrelToSet, UTankTurret* TurretToSet );

	void AimAt( FVector WorldSpaceAim, float LaunchSpeed );

protected:
	UPROPERTY( BlueprintReadOnly, Category = "State" )
	EFiringState FiringState = EFiringState::Locked;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards( FVector AimDirection );	
};
