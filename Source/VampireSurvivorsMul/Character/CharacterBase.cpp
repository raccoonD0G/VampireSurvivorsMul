// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "Component/CharacterStatComponent.h"
#include "Widget/HpBarWidget.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

void ACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CharacterStatComponent = GetComponentByClass<UCharacterStatComponent>();

	check(CharacterStatComponent);

	if (CharacterStatComponent)
	{
		CharacterStatComponent->OnHpZero.AddUObject(this, &ACharacterBase::OnHpZero);
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::InitHpBarWidget(UHpBarWidget* HpBarWidget)
{
	HpBarWidget->UpdateHpBar(CharacterStatComponent->GetCurrentHp(), (CharacterStatComponent->GetCharacterBaseStat() + CharacterStatComponent->GetCharacterModifierStat()).MaxHp);
	CharacterStatComponent->OnHpChanged.AddUObject(HpBarWidget, &UHpBarWidget::UpdateHpBar);
}

void ACharacterBase::OnHpZero()
{
	if (HasAuthority())
	{
		if (!IsPendingKill() && !IsPendingKillPending())
		{
			Destroy();
		}
	}
}
