// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/DungeonMovePlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ADungeonMovePlayerController::ADungeonMovePlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MoveMappingContextObj(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_MovePlayer.IMC_MovePlayer'"));
	if (MoveMappingContextObj.Succeeded())
	{
		MoveMappingContext = MoveMappingContextObj.Object;
	}

}

void ADungeonMovePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
	}

	if (IsLocalController())
	{
		AddInputMappingContext();
	}
}

void ADungeonMovePlayerController::AddInputMappingContext()
{

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer)
	{
		FTimerHandle RetryHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryHandle, FTimerDelegate::CreateUObject(this, &ADungeonMovePlayerController::AddInputMappingContext), 0.1f, false);
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!Subsystem)
	{
		FTimerHandle RetryHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryHandle, FTimerDelegate::CreateUObject(this, &ADungeonMovePlayerController::AddInputMappingContext), 0.1f, false);
		return;
	}

	Subsystem->AddMappingContext(MoveMappingContext, 0);
}
