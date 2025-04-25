// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/DungeonPlayerController.h"
#include "GameState/DungeonGameState.h"

APawn* ADungeonPlayerController::FindMyPawn()
{
	ADungeonGameState* GS = GetWorld()->GetGameState<ADungeonGameState>();
	if (!GS) return nullptr;

	for (const FPlayerPawnPair& Pair : GS->GetPlayerPawnPairs())
	{
		if (Pair.Controller == this)
		{
			return Pair.Pawn;
		}
	}

	return nullptr;
}

void ADungeonPlayerController::Server_RequestPossess_Implementation(APawn* TargetPawn)
{
	if (TargetPawn)
	{
		UE_LOG(LogTemp, Log, TEXT("Server_RequestPossess called by %s for pawn %s"), *GetName(), *TargetPawn->GetName());

		if (!TargetPawn->GetController() || TargetPawn->GetController() == this)
		{
			Possess(TargetPawn);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TargetPawn is already possessed by %s"), *TargetPawn->GetController()->GetName());
		}
	}
}
