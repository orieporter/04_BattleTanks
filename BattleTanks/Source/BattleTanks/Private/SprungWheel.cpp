// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Body Axle Constraint"));
	SetRootComponent(BodyAxleConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(RootComponent);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraints();
}

void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	auto TankRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!TankRoot) { return; }
	BodyAxleConstraint->SetConstrainedComponents(TankRoot, FName(NAME_None), Axle, FName(NAME_None));

	AxleWheelConstraint->SetConstrainedComponents(Axle, FName(NAME_None), Wheel, FName(NAME_None));
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}