// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MeteorShooterComponent.h"
#include "MeteorShooterComponent.h"
#include "Attack/Meteor.h"
#include "Kismet/KismetMathLibrary.h"

UMeteorShooterComponent::UMeteorShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMeteorShooterComponent::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastSpawn = 0.0f;
}

void UMeteorShooterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->HasAuthority())
	{
		TimeSinceLastSpawn += DeltaTime;
		if (TimeSinceLastSpawn >= SpawnInterval)
		{
			SpawnMeteor();
			TimeSinceLastSpawn = 0.0f;
		}
	}
}

void UMeteorShooterComponent::SpawnMeteor()
{
	if (!MeteorClass || !GetOwner()) return;

	FVector OwnerLocation = GetOwner()->GetActorLocation();

	float Angle = FMath::FRandRange(0.f, 2 * PI);
	float Radius = FMath::FRandRange(0.f, SpawnRadius);

	FVector2D RandomOffset2D = FVector2D(FMath::Cos(Angle), FMath::Sin(Angle)) * Radius;

	FVector SpawnLocation = FVector(
		OwnerLocation.X + RandomOffset2D.X,
		OwnerLocation.Y + RandomOffset2D.Y,
		OwnerLocation.Z + SpawnHeight
	);

	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();

	GetWorld()->SpawnActor<AMeteor>(MeteorClass, SpawnLocation, SpawnRotation, SpawnParams);
}

