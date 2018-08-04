// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("%f: Barrel-Elevate() of %s called at speed %f"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName(), RelativeSpeed)
}


