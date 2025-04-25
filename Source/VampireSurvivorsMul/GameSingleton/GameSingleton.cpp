// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSingleton/GameSingleton.h"

UGameSingleton::UGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterStatDataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/CharacterStatTable.CharacterStatTable'"));
	if (nullptr != CharacterStatDataTableRef.Object)
	{
		const UDataTable* DataTable = CharacterStatDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FCharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterStatDataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/MonsterStatTable.MonsterStatTable'"));
	if (nullptr != MonsterStatDataTableRef.Object)
	{
		const UDataTable* DataTable = MonsterStatDataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, MonsterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FMonsterStat*>(Value);
			}
		);
	}

	MonsterMaxLevel = MonsterStatTable.Num();
	ensure(MonsterMaxLevel > 0);
}

UGameSingleton& UGameSingleton::Get()
{
	UGameSingleton* Singleton = CastChecked<UGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogTemp, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UGameSingleton>();
}