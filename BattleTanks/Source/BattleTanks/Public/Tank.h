// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class AProjectile;
class UTankBarrel;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankAimingComponent* AimingComponentToSet);

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 100000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ReloadTimeInSeconds = 3.0f;

	double LastReloadTime = -ReloadTimeInSeconds;

	UTankBarrel* Barrel = nullptr;
};
