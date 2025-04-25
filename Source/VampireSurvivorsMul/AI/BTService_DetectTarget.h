// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectTarget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL_API UBTService_DetectTarget : public UBTService
{
	GENERATED_BODY()
	
public:
    UBTService_DetectTarget();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
    UPROPERTY(EditAnywhere, Category = "Detection")
    TSubclassOf<AActor> TargetClass;

    UPROPERTY(EditAnywhere, Category = "Detection")
    float DetectRadius = 1000.0f;
	
};
