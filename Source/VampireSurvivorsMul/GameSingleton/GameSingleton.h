// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameData/CharacterStat.h"
#include "GameData/MonsterStat.h"
#include "GameSingleton.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API UGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UGameSingleton();
	static UGameSingleton& Get();

// Character Section
public:
	FORCEINLINE FCharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FCharacterStat(); }
	FORCEINLINE const int32 GetCharacterMaxLevel() const { return CharacterMaxLevel; }

private:
	UPROPERTY()
	int32 CharacterMaxLevel;
	TArray<FCharacterStat> CharacterStatTable;

// Monster Section
public:
	FORCEINLINE FMonsterStat GetMonsterStat(int32 InLevel) const { return MonsterStatTable.IsValidIndex(InLevel - 1) ? MonsterStatTable[InLevel - 1] : FMonsterStat(); }
	FORCEINLINE const int32 GetMonsterMaxLevel() const { return MonsterMaxLevel; }

private:
	UPROPERTY()
	int32 MonsterMaxLevel;
	TArray<FMonsterStat> MonsterStatTable;

};
