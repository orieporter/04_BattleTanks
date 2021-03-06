// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	// How close the AI will get to the player
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 3000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Testing")
		bool bCanFire = true; // Set in blueprint for quick testing/debugging

	virtual void SetPawn(APawn * InPawn) override;

	UFUNCTION()
		void OnTankDeath();
};
