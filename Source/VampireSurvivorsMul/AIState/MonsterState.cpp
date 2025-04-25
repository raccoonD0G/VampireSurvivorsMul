// Fill out your copyright notice in the Description page of Project Settings.


#include "AIState/MonsterState.h"

AMonsterState::AMonsterState()
{
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;
}

void AMonsterState::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EMonsterState::Idle);
}

void AMonsterState::SetCurrentState(EMonsterState NewState)
{
	switch (NewState)
	{
	case EMonsterState::Idle:
		break;
	case EMonsterState::Chase:
		break;
	case EMonsterState::Attack:
		break;
	default:
		break;
	}

	CurrentState = NewState;

	OnStateChanged.Broadcast(NewState);
}
