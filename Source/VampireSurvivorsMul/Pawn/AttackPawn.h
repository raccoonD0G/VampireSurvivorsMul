// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AttackPawn.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMouseClickedDelegate, const FInputActionValue& /*Value*/);
UCLASS()
class VAMPIRESURVIVORSMUL_API AAttackPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAttackPawn();

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
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> AttackMappingContext;

	void AddInputMappingContext();

// Attack Section
public:
	FTimerHandle AttackTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackInterval = 0.5f;  // 공격 주기

	void StartAttacking();
	void StopAttacking();
	void TriggerAttackTowardsCursor();

	UFUNCTION(Server, Reliable)
	void Server_TriggerAttackTowardsCursor(const FVector& TargetDirection);
	void Server_TriggerAttackTowardsCursor_Implementation(const FVector& TargetDirection);


	void TriggerMouseClickAttack(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Server_TriggerMouseClickAttack(const FInputActionValue& Value);
	void Server_TriggerMouseClickAttack_Implementation(const FInputActionValue& Value);

	FOnMouseClickedDelegate OnMouseClicked;
};
