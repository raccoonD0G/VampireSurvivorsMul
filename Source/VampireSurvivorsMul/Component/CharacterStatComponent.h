// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/CharacterStat.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHpChangedDelegate, float /*CurrentHp*/, float /*MaxHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCharacterStatChangedDelegate, const FCharacterStat& /*BaseStat*/, const FCharacterStat& /*ModifierStat*/);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRESURVIVORSMUL_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		
// Hp Section
public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	float ApplyDamage(float InDamage);

protected:
	void SetHp(float NewHp);

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHp)
	float CurrentHp;

	UFUNCTION()
	void OnRep_CurrentHp();

// Stat Section
public:
	FOnCharacterStatChangedDelegate OnCharacterStatChanged;
	void SetCharacterLevelStat(int32 InNewLevel);

	FORCEINLINE void SetCharacterBaseStat(const FCharacterStat& InBaseStat) { CharacterBaseStat = InBaseStat; OnCharacterStatChanged.Broadcast(GetCharacterBaseStat(), GetCharacterModifierStat()); }
	FORCEINLINE void SetCharacterModifierStat(const FCharacterStat& InModifierStat) { CharacterModifierStat = InModifierStat; OnCharacterStatChanged.Broadcast(GetCharacterBaseStat(), GetCharacterModifierStat()); }

	FORCEINLINE const FCharacterStat& GetCharacterBaseStat() const { return CharacterBaseStat; }
	FORCEINLINE const FCharacterStat& GetCharacterModifierStat() const { return CharacterModifierStat; }

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentCharacterLevel;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FCharacterStat CharacterBaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FCharacterStat CharacterModifierStat;
};
