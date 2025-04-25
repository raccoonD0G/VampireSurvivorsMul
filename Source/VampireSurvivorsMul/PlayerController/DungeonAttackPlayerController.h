// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/DungeonPlayerController.h"
#include "DungeonAttackPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ADungeonAttackPlayerController : public ADungeonPlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
};
