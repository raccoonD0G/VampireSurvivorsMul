// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorFactory.generated.h"

UCLASS()
class VAMPIRESURVIVORSMUL_API AFloorFactory : public AActor
{
	GENERATED_BODY()

	public:
	AFloorFactory();

	// 바닥 생성 요청
	void SpawnFloorAt(const FVector& Location);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Floor")
	TSubclassOf<class AFloor> FloorClass;

	UPROPERTY(EditAnywhere, Category = "Floor")
	int32 MaxFloorCount = 10;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class AFloor>> SpawnedFloors;
};