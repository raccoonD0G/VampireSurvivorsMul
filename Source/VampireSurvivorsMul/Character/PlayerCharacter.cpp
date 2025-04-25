// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f); //
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TryHandle;
	GetWorld()->GetTimerManager().SetTimer(TryHandle, FTimerDelegate::CreateUObject(this, &APlayerCharacter::AddInputMappingContext), 0.1f, false);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleMove);
	}

}

void APlayerCharacter::AddInputMappingContext()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		FTimerHandle RetryHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryHandle, FTimerDelegate::CreateUObject(this, &APlayerCharacter::AddInputMappingContext), 0.1f, false);
		return;
	}

	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer)
	{
		FTimerHandle RetryHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryHandle, FTimerDelegate::CreateUObject(this, &APlayerCharacter::AddInputMappingContext), 0.1f, false);
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!Subsystem)
	{
		FTimerHandle RetryHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryHandle, FTimerDelegate::CreateUObject(this, &APlayerCharacter::AddInputMappingContext), 0.1f, false);
		return;
	}

	Subsystem->AddMappingContext(MoveMappingContext, 0);
}


void APlayerCharacter::HandleMove(const FInputActionValue& Value)
{
	FVector2D MoveInput = Value.Get<FVector2D>();

	if (MoveInput.IsNearlyZero())
	{
		return;
	}

	FRotator CameraRotation = GetControlRotation();
	CameraRotation.Pitch = 0.f;
	CameraRotation.Roll = 0.f;

	FVector Forward = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X);
	FVector Right = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, MoveInput.Y);
	AddMovementInput(Right, MoveInput.X);

	FVector MoveDirection = (Forward * MoveInput.Y + Right * MoveInput.X).GetSafeNormal();
	Server_HandleMove(MoveDirection);
}

void APlayerCharacter::Server_HandleMove_Implementation(const FVector& MoveDirection)
{
	if (MoveDirection.IsNearlyZero())
	{
		return;
	}

	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = MoveDirection.Rotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f);

	SetActorRotation(NewRotation);
}
