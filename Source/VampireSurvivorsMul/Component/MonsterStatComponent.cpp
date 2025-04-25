// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MonsterStatComponent.h"
#include "GameSingleton/GameSingleton.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UMonsterStatComponent::UMonsterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentMonsterLevel = 1;
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
}

void UMonsterStatComponent::SetMonsterLevelStat(int32 InNewLevel)
{
	CurrentMonsterLevel = FMath::Clamp(InNewLevel, 1, UGameSingleton::Get().GetMonsterMaxLevel());
	SetMonsterBaseStat(UGameSingleton::Get().GetMonsterStat(CurrentMonsterLevel));
}


