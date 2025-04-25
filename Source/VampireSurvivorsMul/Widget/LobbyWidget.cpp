// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LobbyWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/VSGameInstance.h"
#include "Components/Button.h"

void ULobbyWidget::NativeConstruct()
{
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnJoinButtonClicked);
	}
}

void ULobbyWidget::OnJoinButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Join button clicked"));

	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld()))
	{
		if (UVSGameInstance* VSGameInstance = Cast<UVSGameInstance>(GameInstance))
		{
			VSGameInstance->RequestJoinMatch();
		}
	}
}