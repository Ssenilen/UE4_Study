// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "GSAIController.h"
#include "GSCharacter.h"


UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AGSCharacter* GSCharacter = Cast<AGSCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == GSCharacter)
		return EBTNodeResult::Failed;

	GSCharacter->Attack();
	IsAttacking = true;
	GSCharacter->OnAttackEnd.AddLambda([this]() {
		IsAttacking = false;
	});


	// ���� �ִϸ��̼��� ���� ������ ����ؾ� �ϹǷ� InProgress ���¿��� �Ѵ�.
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (IsAttacking == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

