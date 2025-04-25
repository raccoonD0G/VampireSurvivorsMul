// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/DungeonPlayerController.h"
#include "DungeonMovePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ADungeonMovePlayerController : public ADungeonPlayerController
{
	GENERATED_BODY()
	
public:
	ADungeonMovePlayerController();

protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> MoveMappingContext;

private:
	UFUNCTION()
	void AddInputMappingContext();

	
};
