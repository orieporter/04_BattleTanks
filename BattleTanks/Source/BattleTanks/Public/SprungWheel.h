// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent * Mass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent * Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UPhysicsConstraintComponent * PhysicsConstraint = nullptr;
};
