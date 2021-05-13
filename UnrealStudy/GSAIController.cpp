// Fill out your copyright notice in the Description page of Project Settings.


#include "GSAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AGSAIController::AGSAIController()
{
	RepeatInterval = 3.0f;
}

void AGSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AGSAIController::OnRepeatTimer, RepeatInterval, true);
}

void AGSAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AGSAIController::OnRepeatTimer()
{
	APawn* CurrentPawn = GetPawn();
	check(CurrentPawn);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (NavSystem == nullptr) return;

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		debugf(TEXT("Next Location: %s"), *NextLocation.Location.ToString());
	}
}