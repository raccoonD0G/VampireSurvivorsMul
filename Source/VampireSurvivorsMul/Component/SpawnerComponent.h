// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnerComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAMPIRESURVIVORSMUL_API USpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	USpawnerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> SpawnActorClasses;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	float SpawnRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	float SpawnInterval = 1.0f;

	float TimeSinceLastSpawn = 0.0f;

	void SpawnRandomActor();
};
