// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/LobbyPlayerController.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
