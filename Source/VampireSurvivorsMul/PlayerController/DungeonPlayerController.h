// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ADungeonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APawn* FindMyPawn();

	UFUNCTION(Server, Reliable)
	void Server_RequestPossess(APawn* TargetPawn);
	void Server_RequestPossess_Implementation(APawn* TargetPawn);
};
