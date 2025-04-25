// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HpBarWidgetInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class VAMPIRESURVIVORSMUL_API ACharacterBase : public ACharacter, public IHpBarWidgetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Stat Section
public:
	FORCEINLINE class UCharacterStatComponent* GetCharacterStatComponent() { return CharacterStatComponent; }
	virtual void InitHpBarWidget(class UHpBarWidget* HpBarWidget) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCharacterStatComponent> CharacterStatComponent;

// Dead Section
protected:
	virtual void OnHpZero();

};
