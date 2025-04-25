// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CharacterStatComponent.h"
#include "GameSingleton/GameSingleton.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;

	CurrentCharacterLevel = 1;
	SetIsReplicatedByDefault(true);
}


void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetCharacterLevelStat(CurrentCharacterLevel);
	SetHp(CharacterBaseStat.MaxHp);
}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterStatComponent, CurrentHp);
}

float UCharacterStatComponent::ApplyDamage(float InDamage)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return 0.0f;
	}

	SetHp(CurrentHp - InDamage);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return InDamage;
}


void UCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp(NewHp, 0.0f, CharacterBaseStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHp, CharacterBaseStat.MaxHp);
}

void UCharacterStatComponent::OnRep_CurrentHp()
{
	OnHpChanged.Broadcast(CurrentHp, CharacterBaseStat.MaxHp);
}

void UCharacterStatComponent::SetCharacterLevelStat(int32 InNewLevel)
{
	CurrentCharacterLevel = FMath::Clamp(InNewLevel, 1, UGameSingleton::Get().GetCharacterMaxLevel());
	SetCharacterBaseStat(UGameSingleton::Get().GetCharacterStat(CurrentCharacterLevel));
	check(CharacterBaseStat.MaxHp > 0.0f);
}

