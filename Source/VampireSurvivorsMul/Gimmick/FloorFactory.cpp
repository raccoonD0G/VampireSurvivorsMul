// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/FloorFactory.h"
#include "Floor.h"
#include "Engine/World.h"

AFloorFactory::AFloorFactory()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFloorFactory::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SpawnFloorAt(FVector(0.0f, 0.0f, -0.5f));
	}
}

void AFloorFactory::SpawnFloorAt(const FVector& Location)
{
	if (!FloorClass) return;

	for (AFloor* Existing : SpawnedFloors)
	{
		if (Existing && Existing->GetActorLocation().Equals(Location, 1.f))
		{
			return;
		}
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AFloor* NewFloor = GetWorld()->SpawnActor<AFloor>(FloorClass, Location, FRotator::ZeroRotator, SpawnParams);
	check(NewFloor);
	if (!NewFloor) return;

	if (SpawnedFloors.Num() == 0)
	{
		NewFloor->Init(this, 1);
	}
	else
	{
		NewFloor->Init(this);
	}

	// 배열에 추가
	SpawnedFloors.Add(NewFloor);

	// 초과 시 가장 오래된 것 제거
	if (SpawnedFloors.Num() > MaxFloorCount)
	{
		AFloor* OldFloor = SpawnedFloors[0];
		if (OldFloor && !OldFloor->IsPendingKill())
		{
			OldFloor->Destroy();
		}
		SpawnedFloors.RemoveAt(0);
	}
}
