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
		UE_LOG(LogTemp, Warning, TEXT("[ApplyDamage] Not Server"));
		return 0.0f;
	}

	UE_LOG(LogTemp, Warning, TEXT("[ApplyDamage] InDamage: %.1f, CurrentHp before: %.1f"), InDamage, CurrentHp);

	SetHp(CurrentHp - InDamage);

	UE_LOG(LogTemp, Warning, TEXT("[ApplyDamage] CurrentHp after: %.1f"), CurrentHp);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ApplyDamage] 0, Dead"));
		OnHpZero.Broadcast();
	}

	return InDamage;
}


void UCharacterStatComponent::SetHp(float NewHp)
{
	UE_LOG(LogTemp, Warning, TEXT("[SetHp] %.1f -> %.1f (MaxHp: %.1f)"), CurrentHp, NewHp, CharacterBaseStat.MaxHp);

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

