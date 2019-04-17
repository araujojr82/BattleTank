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
class AProjectile;

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION( BlueprintCallable, Category = "Setup" )
	void Initialise( UTankBarrel* BarrelToSet, UTankTurret* TurretToSet );

	void AimAt( FVector WorldSpaceAim );

	UFUNCTION( BlueprintCallable )
	void Fire();

protected:
	UPROPERTY( BlueprintReadOnly, Category = "State" )
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;

	void MoveBarrelTowards( FVector AimDirection );

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float LaunchSpeed = 4000;

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float ReloadTimeInSeconds = 3;

	float LastFireTime = 0;

};
