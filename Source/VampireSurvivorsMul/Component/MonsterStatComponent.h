// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/CharacterStatComponent.h"
#include "GameData/MonsterStat.h"
#include "MonsterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMonsterStatChangedDelegate, const FMonsterStat& /*BaseStat*/, const FMonsterStat& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRESURVIVORSMUL_API UMonsterStatComponent : public UCharacterStatComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterStatComponent();

	// Stat Section
public:
	FOnMonsterStatChangedDelegate OnMonsterStatChanged;
	void SetMonsterLevelStat(int32 InNewLevel);

	FORCEINLINE void SetMonsterBaseStat(const FMonsterStat& InBaseStat) { MonsterBaseStat = InBaseStat; OnMonsterStatChanged.Broadcast(GetMonsterBaseStat(), GetCharacterModifierStat()); }
	FORCEINLINE void SetMonsterModifierStat(const FMonsterStat& InModifierStat) { MonsterModifierStat = InModifierStat; OnMonsterStatChanged.Broadcast(GetMonsterBaseStat(), GetCharacterModifierStat()); }

	FORCEINLINE const FMonsterStat& GetMonsterBaseStat() const { return MonsterBaseStat; }
	FORCEINLINE const FMonsterStat& GetCharacterModifierStat() const { return MonsterModifierStat; }

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentMonsterLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FMonsterStat MonsterBaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FMonsterStat MonsterModifierStat;
};
