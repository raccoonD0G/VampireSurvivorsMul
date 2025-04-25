// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/StateAIController.h"
#include "AIState/MonsterState.h"
#include "Interface/DetectServiceInterface.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API AMonsterController : public AStateAIController, public IDetectServiceInterface
{
	GENERATED_BODY()
	
public:
	AMonsterController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

// State Section
private:
	void SetBlackBoardState(EMonsterState NewState);

// Detect Section
public:
	virtual void SetDetectedActor(AActor* NewDetectedActor) override;
	FOnTargetActorDetectedDelegate OnTargetActorDetected;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> DetectedActor;

};
