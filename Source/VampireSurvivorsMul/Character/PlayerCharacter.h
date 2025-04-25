// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class VAMPIRESURVIVORSMUL_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Input Section
protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> MoveMappingContext;

private:
	UFUNCTION()
	void AddInputMappingContext();

// Move Section
public:
	UFUNCTION()
	void HandleMove(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Server_HandleMove(const FVector& MoveDirection);
	void Server_HandleMove_Implementation(const FVector& MoveDirection);
	
};
