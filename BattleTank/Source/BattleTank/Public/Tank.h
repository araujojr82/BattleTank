// Copyright Euclides Araujo 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable )
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;
	
	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	TSubclassOf<AProjectile> ProjectileBluePrint;

	// TODO remove after moving to Aiming Component
	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float LaunchSpeed = 4000;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float ReloadTimeInSeconds = 3;

	// Local barrel refrence for spawing projectile
	UTankBarrel* Barrel = nullptr;	// TODO Remove
	
	float LastFireTime = 0;

};