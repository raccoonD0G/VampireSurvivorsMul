// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/MonsterController.h"
#include "AIState/MonsterState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI.h"

AMonsterController::AMonsterController()
{
	AIStateClass = AMonsterState::StaticClass();
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMonsterState* MonsterState = Cast<AMonsterState>(GetAIState());
	check(MonsterState);

	if (MonsterState)
	{
		MonsterState->OnStateChanged.AddUObject(this, &AMonsterController::SetBlackBoardState);
	}
}

void AMonsterController::SetBlackBoardState(EMonsterState NewState)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (BlackboardPtr)
	{
		BlackboardPtr->SetValueAsEnum(BBKEY_MONSTERSTATE, static_cast<uint8>(NewState));
	}
}

void AMonsterController::SetDetectedActor(AActor* NewDetectedActor)
{
	DetectedActor = NewDetectedActor;
	OnTargetActorDetected.Broadcast(NewDetectedActor);

	AMonsterState* MonsterState = Cast<AMonsterState>(GetAIState());
	check(MonsterState);

	if (MonsterState)
	{
		if (MonsterState->GetCurrentState() == EMonsterState::Idle)
		{
			MonsterState->SetCurrentState(EMonsterState::Chase);
		}
	}
}
