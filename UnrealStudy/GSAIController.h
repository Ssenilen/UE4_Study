// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "AIController.h"
#include "GSAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AGSAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AGSAIController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
