// Fill out your copyright notice in the Description page of Project Settings.


#include "GSAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AGSAIController::HomePosKey(TEXT("HomePos"));
const FName AGSAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AGSAIController::TargetKey(TEXT("Target"));

AGSAIController::AGSAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Book/AI/BB_GSCharacter.BB_GSCharacter"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Book/AI/BT_GSCharacter.BT_GSCharacter"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AGSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			debugf(TEXT("AIController couldn't run behavior tree!"));
		}
	}
}