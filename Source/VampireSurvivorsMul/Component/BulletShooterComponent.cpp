// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BulletShooterComponent.h"
#include "Attack/Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBulletShooterComponent::UBulletShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBulletShooterComponent::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastFire = 0.0f;
}

void UBulletShooterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->HasAuthority())
	{
		TimeSinceLastFire += DeltaTime;
		if (TimeSinceLastFire >= FireInterval)
		{
			FireBullet();
			TimeSinceLastFire = 0.0f;
		}
	}
}

void UBulletShooterComponent::FireBullet()
{
	if (!BulletClass) return;

	AActor* Owner = GetOwner();
	if (!Owner) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FVector SpawnLocation = GetComponentLocation();
	FRotator SpawnRotation = Owner->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Owner->GetInstigator();

	World->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);
}