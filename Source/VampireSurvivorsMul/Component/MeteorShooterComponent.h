// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MeteorShooterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRESURVIVORSMUL_API UMeteorShooterComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeteorShooterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMeteor> MeteorClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnInterval = 2.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnRadius = 1000.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnHeight = 500.0f;

	float TimeSinceLastSpawn = 0.0f;

	void SpawnMeteor();
};
