// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;

	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);
	for (USceneComponent * Child : Children)
	{
		auto SpawnPoint = Cast<USpawnPoint>(Child);
		if (!SpawnPoint) { continue; }
		auto Wheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
		if (!Wheel) { continue; }

		Wheels.Push(Wheel);

	}
	return Wheels;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel * Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}