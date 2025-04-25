// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnJoinButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton>  JoinButton;

};
