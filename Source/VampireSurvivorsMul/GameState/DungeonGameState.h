// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonGameState.generated.h"

USTRUCT(BlueprintType)
struct FPlayerPawnPair
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<APlayerController> Controller;

	UPROPERTY()
	TObjectPtr<APawn> Pawn;
};


/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ADungeonGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

// Pawn Section
public:
	FORCEINLINE TArray<FPlayerPawnPair>& GetPlayerPawnPairs() { return PlayerPawnPairs; }

private:
	UFUNCTION()
	void OnRep_PlayerPawnPairs();

	UPROPERTY(ReplicatedUsing = OnRep_PlayerPawnPairs)
	TArray<FPlayerPawnPair> PlayerPawnPairs;
	
};
