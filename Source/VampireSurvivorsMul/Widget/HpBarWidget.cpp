// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/HpBarWidgetInterface.h"
#include "Component/CharacterStatComponent.h"

void UHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(HpBar);

	IHpBarWidgetInterface* HpBarWidgetInterface = Cast<IHpBarWidgetInterface>(OwningActor);
	if (HpBarWidgetInterface)
	{
		HpBarWidgetInterface->InitHpBarWidget(this);
	}
	
}

void UHpBarWidget::UpdateHpBar(float CurrentHp, float MaxHp)
{
	if (!HpBar || CurrentHp <= 0.0f)
	{
		return;
	}

	const float HpPercent = CurrentHp / MaxHp;
	HpBar->SetPercent(HpPercent);
}
