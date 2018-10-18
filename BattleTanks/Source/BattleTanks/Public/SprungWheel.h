// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASprungWheel();

	void AddDrivingForce(float ForceMagnitude);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent * Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent * Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UPhysicsConstraintComponent * BodyAxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
		UPhysicsConstraintComponent * AxleWheelConstraint = nullptr;

	float TotalForceMagnitude = 0.0f;

	void SetupConstraints();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
