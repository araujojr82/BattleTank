// Copyright Euclides Araujo 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI Tank get
	UPROPERTY( EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;
	
private:
	virtual void BeginPlay() override;

	virtual void SetPawn( APawn* InPawn ) override;

	virtual void Tick( float DeltaTime ) override;	

	UFUNCTION()
	void OnTankDeath();
};
