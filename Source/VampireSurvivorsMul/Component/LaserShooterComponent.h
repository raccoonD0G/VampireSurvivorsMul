// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LaserShooterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRESURVIVORSMUL_API ULaserShooterComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULaserShooterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "ture"))
	TSubclassOf<class ALaser> LaserClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class AAttackPawn> AttackPawn;

	void ShootLaser(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Server_ShootLaser(const FVector& ShootDirection);
	void Server_ShootLaser_Implementation(const FVector& ShootDirection);
		
};
