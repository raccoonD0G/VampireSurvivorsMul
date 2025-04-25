// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LaserShooterComponent.h"
#include "Pawn/AttackPawn.h"

// Sets default values for this component's properties
ULaserShooterComponent::ULaserShooterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void ULaserShooterComponent::BeginPlay()
{
	Super::BeginPlay();

	AttackPawn = Cast<AAttackPawn>(GetOwner());
	check(AttackPawn);

	AttackPawn->OnMouseClicked.AddUObject(this, &ULaserShooterComponent::ShootLaser);
}


// Called every frame
void ULaserShooterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULaserShooterComponent::ShootLaser(const FInputActionValue& Value)
{
	if (!LaserClass) return;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC || !PC->IsLocalController()) return;

	FVector WorldLocation, WorldDirection;
	if (PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		// 서버에 방향 전달
		Server_ShootLaser(WorldDirection);
	}
}

void ULaserShooterComponent::Server_ShootLaser_Implementation(const FVector& ShootDirection)
{
	if (!LaserClass || !GetWorld()) return;

	FVector SpawnLocation = GetComponentLocation();
	FRotator SpawnRotation = ShootDirection.Rotation();
	SpawnRotation.Pitch = 0.0f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());

	GetWorld()->SpawnActor<ALaser>(LaserClass, SpawnLocation, SpawnRotation, SpawnParams);
}
