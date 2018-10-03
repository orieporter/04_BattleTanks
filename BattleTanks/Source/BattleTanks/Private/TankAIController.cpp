// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
// MoveToActor depends on TankMovementComponent::RequestDirectMove()





void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (ensure(ControlledTank) && ensure(PlayerPawn))
	{
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

		MoveToActor(PlayerPawn, AcceptanceRadius);

		if (ensure(AimingComponent))
		{
			AimingComponent->AimAt(PlayerPawn->GetActorLocation());
			if (AimingComponent->GetFiringState() == EFiringState::Locked)
			{
				AimingComponent->Fire();
			}
		}
	}
}

void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}
