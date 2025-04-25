// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attack/AttackBase.h"
#include "Bullet.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API ABullet : public AAttackBase
{
	GENERATED_BODY()
	
public:
	ABullet();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
};
