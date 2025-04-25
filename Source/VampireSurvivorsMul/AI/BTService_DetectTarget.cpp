// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/DetectServiceInterface.h"
#include "AI/AI.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
    bNotifyBecomeRelevant = true;
    bNotifyTick = true;
    NodeName = TEXT("Detect Target Actor");
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* AIPawn = AIController ? AIController->GetPawn() : nullptr;
    if (!AIPawn || !TargetClass) return;

    FVector Location = AIPawn->GetActorLocation();
    UWorld* World = AIPawn->GetWorld();

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(AIPawn);

    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(DetectRadius);

    bool bHasOverlap = World->OverlapMultiByObjectType(
        Overlaps,
        Location,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
        CollisionShape,
        QueryParams
    );

#if WITH_EDITOR
    // DrawDebugSphere(World, Location, DetectRadius, 16, FColor::Green, false, 1.0f);
#endif

    AActor* NearestActor = nullptr;
    float ClosestDist = DetectRadius;

    if (bHasOverlap)
    {
        for (const FOverlapResult& Result : Overlaps)
        {
            AActor* Actor = Result.GetActor();
            if (!Actor || !Actor->IsA(TargetClass)) continue;

            float Dist = FVector::Dist(Actor->GetActorLocation(), Location);
            if (Dist < ClosestDist)
            {
                ClosestDist = Dist;
                NearestActor = Actor;
            }
        }
    }

    if (NearestActor)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_DETECTEDTARGET, NearestActor);

        IDetectServiceInterface* DetectServiceInterface = Cast<IDetectServiceInterface>(OwnerComp.GetOwner());
        if (DetectServiceInterface)
        {
            DetectServiceInterface->SetDetectedActor(NearestActor);
        }
    }
}
