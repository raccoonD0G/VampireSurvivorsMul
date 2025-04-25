// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DetectServiceInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetActorDetectedDelegate, AActor* /*NewDetectedActor*/)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDetectServiceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRESURVIVORSMUL_API IDetectServiceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetDetectedActor(AActor* NewDetectedActor) = 0;
};
