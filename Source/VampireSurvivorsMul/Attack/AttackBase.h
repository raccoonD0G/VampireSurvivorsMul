// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackBase.generated.h"

UCLASS()
class VAMPIRESURVIVORSMUL_API AAttackBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttackBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// Collision Section
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UShapeComponent> ShapeComponent;

// Damage Section
public:
	virtual float GetDamage() const;

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
