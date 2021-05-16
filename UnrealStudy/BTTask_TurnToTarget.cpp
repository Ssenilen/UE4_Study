// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "GSCharacter.h"
#include "GSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
    NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    AGSCharacter* GSCharacter = Cast<AGSCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (nullptr == GSCharacter)
        return EBTNodeResult::Failed;

    AGSCharacter* Target = Cast<AGSCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGSAIController::TargetKey));
    if (nullptr == GSCharacter)
        return EBTNodeResult::Failed;

    FVector LookVector = Target->GetActorLocation() - GSCharacter->GetActorLocation();
    LookVector.Z = 0.0f;

    FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
    GSCharacter->SetActorRotation(FMath::RInterpTo(GSCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

    return EBTNodeResult::Succeeded;
}
