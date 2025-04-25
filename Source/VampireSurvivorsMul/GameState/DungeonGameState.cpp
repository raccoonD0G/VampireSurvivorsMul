// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/DungeonGameState.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/DungeonPlayerController.h"

void ADungeonGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADungeonGameState, PlayerPawnPairs);
}

void ADungeonGameState::OnRep_PlayerPawnPairs()
{
	APlayerController* LocalPC = GetWorld()->GetFirstPlayerController();
	if (!LocalPC || !LocalPC->IsLocalController()) return;

	ADungeonPlayerController* DungeonPlayerController = Cast<ADungeonPlayerController>(LocalPC);
	if (!DungeonPlayerController) return;

	for (const FPlayerPawnPair& Pair : PlayerPawnPairs)
	{
		if (Pair.Controller == DungeonPlayerController)
		{
			DungeonPlayerController->Server_RequestPossess(Pair.Pawn);
			break;
		}
	}
}
