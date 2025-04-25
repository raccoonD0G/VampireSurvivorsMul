// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DungeonGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameState/DungeonGameState.h"

void ADungeonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AActor* PlayerStart = UGameplayStatics::GetActorOfClass(this, APlayerStart::StaticClass());
	if (!PlayerStart) return;

	FTransform SpawnTransform = PlayerStart->GetActorTransform();
	APawn* NewPawn = nullptr;

	if (ConnectedPlayerCount == 0)
	{
		NewPawn = GetWorld()->SpawnActor<APawn>(MoveRelayPawnClass, SpawnTransform);
		CachedMovePawn = NewPawn;
	}
	else if (ConnectedPlayerCount == 1)
	{
		NewPawn = GetWorld()->SpawnActor<APawn>(AttackRelayPawnClass, SpawnTransform);

		if (NewPawn && CachedMovePawn)
		{
			NewPawn->AttachToActor(CachedMovePawn, FAttachmentTransformRules::KeepRelativeTransform);
			NewPawn->SetActorRelativeLocation(FVector(0, 0, 0));
		}
	}

	if (ADungeonGameState* GS = GetGameState<ADungeonGameState>())
	{
		FPlayerPawnPair Pair;
		Pair.Controller = NewPlayer;
		Pair.Pawn = NewPawn;
		GS->GetPlayerPawnPairs().Add(Pair);
	}

	ConnectedPlayerCount++;
}

APlayerController* ADungeonGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	UWorld* World = GetWorld();
	if (!World) return nullptr;

	TSubclassOf<APlayerController> ControllerClassToSpawn = nullptr;

	if (ConnectedPlayerCount == 0)
	{
		ControllerClassToSpawn = MovePlayerControllerClass;
	}
	else
	{
		ControllerClassToSpawn = AttackPlayerControllerClass;
	}

	APlayerController* NewPC = World->SpawnActor<APlayerController>(ControllerClassToSpawn);

	return NewPC;
}
