// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIState/AIState.h"
#include "MonsterState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChangedDelegate, EMonsterState /*NewState*/);

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Chase,
	Attack,
};

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API AMonsterState : public AAIState
{
	GENERATED_BODY()
	
public:
	AMonsterState();

protected:
	virtual void BeginPlay() override;

// State Section
public:
	FORCEINLINE const EMonsterState& GetCurrentState() const { return CurrentState; }
	void SetCurrentState(EMonsterState NewState);

	FOnStateChangedDelegate OnStateChanged;

private:
	EMonsterState CurrentState;


};
