// Fill out your copyright notice in the Description page of Project Settings.


#include "GSPlayerController.h"


void AGSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AGSPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	debugf(TEXT("AGSPlayerController::PostInitializeComponents"));
}

void AGSPlayerController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);
	debugf(TEXT("AGSPlayerController::OnPossess"));
}
