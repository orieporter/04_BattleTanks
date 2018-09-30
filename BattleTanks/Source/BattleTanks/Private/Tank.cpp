// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(Damage, 0.0f, CurrentHealth);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0.0f)
	{
		Destroy();
	}

	return 0.0f;
}
