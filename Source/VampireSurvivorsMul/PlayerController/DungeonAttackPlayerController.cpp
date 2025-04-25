// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/DungeonAttackPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ADungeonAttackPlayerController::ADungeonAttackPlayerController()
{
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> AttackMappingContextObj(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_AttackPlayer.IMC_AttackPlayer'"));
    if (AttackMappingContextObj.Succeeded())
    {
        AttackMappingContext = AttackMappingContextObj.Object;
    }
}

void ADungeonAttackPlayerController::BeginPlay()
{
	Super::BeginPlay();

    if (IsLocalController())
    {

        bShowMouseCursor = true;
        bEnableClickEvents = true;
        bEnableMouseOverEvents = true;

        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        SetInputMode(InputMode);
    }

    if (IsLocalController())
    {
        AddInputMappingContext();
    }
}

void ADungeonAttackPlayerController::AddInputMappingContext()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!Subsystem)
	{
		FTimerHandle ReTryHandle;
		GetWorld()->GetTimerManager().SetTimer(ReTryHandle, FTimerDelegate::CreateUObject(this, &ADungeonAttackPlayerController::AddInputMappingContext), 0.1f, false);
		return;
	}

	Subsystem->AddMappingContext(AttackMappingContext, 0);
}
