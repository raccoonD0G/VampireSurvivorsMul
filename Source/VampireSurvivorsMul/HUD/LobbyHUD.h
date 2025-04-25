// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ALobbyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

// HUD Section
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> LobbyWidgetClass;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UUserWidget> LobbyWidget;
};
