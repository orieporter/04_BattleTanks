// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto SafeNewElevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	//UE_LOG(LogTemp, Warning, TEXT("%s %f"), *GetOwner()->GetName(), RelativeSpeed)
	SetRelativeRotation(FRotator(SafeNewElevation, 0.0f, 0.0f));
}


