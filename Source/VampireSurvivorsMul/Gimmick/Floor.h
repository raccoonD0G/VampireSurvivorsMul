// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floor.generated.h"

UCLASS()
class VAMPIRESURVIVORSMUL_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void Init(class AFloorFactory* NewFloorFactory, int32 CurrentNumPlayerInside = 0)
	{
		FloorFactory = NewFloorFactory; 
		NumPlayerInside = CurrentNumPlayerInside;
	}

private:
	UPROPERTY()
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY()
	bool bPlayerWasInside = true;

	UPROPERTY(EditAnywhere)
	float TileSize = 5000.f;

	UPROPERTY()
	TObjectPtr<class AFloorFactory> FloorFactory;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	int32 NumPlayerInside = 0;


};
