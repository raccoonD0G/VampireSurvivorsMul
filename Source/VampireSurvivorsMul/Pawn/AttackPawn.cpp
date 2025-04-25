// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/AttackPawn.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AAttackPawn::AAttackPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AAttackPawn::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TryHandle;
	GetWorld()->GetTimerManager().SetTimer(TryHandle, FTimerDelegate::CreateUObject(this, &AAttackPawn::AddInputMappingContext), 0.1f, false);

	StartAttacking();
}

// Called every frame
void AAttackPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAttackPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &AAttackPawn::TriggerMouseClickAttack);
	}
}


void AAttackPawn::AddInputMappingContext()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());

	if (!PC)
	{
		FTimerHandle ReTryHandle;
		GetWorld()->GetTimerManager().SetTimer(ReTryHandle, FTimerDelegate::CreateUObject(this, &AAttackPawn::AddInputMappingContext), 0.1f, false);
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	if (!Subsystem)
	{
		FTimerHandle ReTryHandle;
		GetWorld()->GetTimerManager().SetTimer(ReTryHandle, FTimerDelegate::CreateUObject(this, &AAttackPawn::AddInputMappingContext), 0.1f, false);
		return;
	}

	Subsystem->AddMappingContext(AttackMappingContext, 0);
}

void AAttackPawn::StartAttacking()
{
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AAttackPawn::TriggerAttackTowardsCursor, AttackInterval, true);
}

void AAttackPawn::StopAttacking()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void AAttackPawn::TriggerAttackTowardsCursor()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	FVector WorldLocation;
	FVector WorldDirection;
	if (PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = Start + WorldDirection * 10000.f;

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);

		FVector TargetLocation = Hit.bBlockingHit ? Hit.ImpactPoint : End;
		FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();

		Server_TriggerAttackTowardsCursor(Direction);
	}
}

void AAttackPawn::Server_TriggerAttackTowardsCursor_Implementation(const FVector& TargetDirection)
{
	
}

void AAttackPawn::TriggerMouseClickAttack(const FInputActionValue& Value)
{
	OnMouseClicked.Broadcast(Value);
	Server_TriggerMouseClickAttack(Value);
}

void AAttackPawn::Server_TriggerMouseClickAttack_Implementation(const FInputActionValue& Value)
{
	
}

