// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlling %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Tank Not Valid"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return;  }

	FVector HitLocation;
	// Get world location if linetrace through crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
	}
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// Find the crosshair position
	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrosshairXLocation), (ViewportSizeY*CrosshairYLocation));
	// De-project the position of the crosshair to a world direction
	OutHitLocation = FVector(1.0);
	// LineTrace through crosshair with landscape collision (up to max range)

	return true;
}