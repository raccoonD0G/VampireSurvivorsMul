// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

// Pawn Section
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Pawn Classes")
	TSubclassOf<APawn> MoveRelayPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Pawn Classes")
	TSubclassOf<APawn> AttackRelayPawnClass;

private:
	int32 ConnectedPlayerCount = 0;

	UPROPERTY()
	TObjectPtr<APawn> CachedMovePawn;

// Controller Section
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerController> MovePlayerControllerClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerController> AttackPlayerControllerClass;

};
