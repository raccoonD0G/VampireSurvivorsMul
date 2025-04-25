// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyHUD.h"
#include "Blueprint/UserWidget.h" 
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (LobbyWidgetClass)
	{
		LobbyWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), LobbyWidgetClass);
		if (LobbyWidget)
		{
			LobbyWidget->AddToViewport();
		}
	}
}
