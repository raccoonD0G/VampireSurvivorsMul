// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ActorOwnableUserWidget.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API UHpBarWidget : public UActorOwnableUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

// Stat Section
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCharacterStatComponent> CharacterStatComponent;

// UI Section
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpBar;

public:
	void UpdateHpBar(float CurrentHp, float MaxHp);
};
