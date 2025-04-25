// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/Floor.h"
#include "Gimmick/FloorFactory.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Character/PlayerCharacter.h"
#include "Collision/Collision.h"

AFloor::AFloor()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

void AFloor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AFloor::OnOverlapEnd);
	}
}

void AFloor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxComponent = GetComponentByClass<UBoxComponent>();
	check(BoxComponent);
}

void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA<APlayerCharacter>())
	{
		FVector MyLocation = GetActorLocation();

		TArray<FVector> Directions = {
			FVector(TileSize, 0, 0),
			FVector(-TileSize, 0, 0),
			FVector(0, TileSize, 0),
			FVector(0, -TileSize, 0)
		};

		for (const FVector& Dir : Directions)
		{
			FVector CheckLocation = MyLocation + Dir;

			TArray<AActor*> OverlappingActors;
			UKismetSystemLibrary::SphereOverlapActors(
				GetWorld(),
				CheckLocation,
				100.f,
				TArray<TEnumAsByte<EObjectTypeQuery>>{UEngineTypes::ConvertToObjectType(CCHANNEL_FLOOR)},
				AFloor::StaticClass(),
				TArray<AActor*>(),
				OverlappingActors
			);

			if (OverlappingActors.Num() == 0)
			{
				FloorFactory->SpawnFloorAt(CheckLocation);
			}
		}
	}
}


