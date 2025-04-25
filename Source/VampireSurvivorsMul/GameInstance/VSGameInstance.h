// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "VSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API UVSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	void RequestJoinMatch();

private:
	void OnJoinMatchResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
