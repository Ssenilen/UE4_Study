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
	virtual void OnUnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
};
