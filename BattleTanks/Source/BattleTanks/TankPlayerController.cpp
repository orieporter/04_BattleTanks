// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"))
	}

	auto ControlledTank = GetControlledTank();
	if (ensure(ControlledTank))
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
	if (!ensure(GetControlledTank())) { return;  }

	FVector HitLocation;
	// Get world location if linetrace through crosshair
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrosshairXLocation), (ViewportSizeY*CrosshairYLocation));

	// De-project the position of the crosshair to a world direction
	FVector LookDirection;
	FVector CameraWorldLocation;
	if (GetLookDirection(ScreenLocation, LookDirection, CameraWorldLocation))
	{
		// LineTrace through crosshair with landscape collision (up to max range)
		return GetLookVectorHitLocation(OutHitLocation, CameraWorldLocation, LookDirection);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't get look direction"));		
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& CameraWorldLocation) const
{
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	//UE_LOG(LogTemp, Warning, TEXT("CameraWorldLocation: %s"), *CameraWorldLocation.ToString())
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector CameraWorldLocation, FVector LookDirection) const
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(""), false, GetPawn());
	if (GetWorld()->LineTraceSingleByChannel(Hit, CameraWorldLocation, CameraWorldLocation + (LookDirection*LineTraceRange), ECollisionChannel::ECC_Visibility, QueryParams))
	{
		HitLocation = Hit.Location;
		return true;
	}

	Hit.Location = FVector(0.0f);
	
	return false;
}

