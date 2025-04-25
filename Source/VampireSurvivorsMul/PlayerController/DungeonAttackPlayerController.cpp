// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/DungeonAttackPlayerController.h"

void ADungeonAttackPlayerController::BeginPlay()
{
	Super::BeginPlay();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    SetInputMode(InputMode);
}
