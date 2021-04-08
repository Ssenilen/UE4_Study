// Fill out your copyright notice in the Description page of Project Settings.


#include "GSGameMode.h"
#include "GSPawn.h"
#include "GSPlayerController.h"

AGSGameMode::AGSGameMode()
{
	DefaultPawnClass = AGSPawn::StaticClass();
	PlayerControllerClass = AGSPlayerController::StaticClass();
}

void AGSGameMode::PostLogin(APlayerController* NewPlayer)
{
	debugf(TEXT("AGSGameMode::PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	debugf(TEXT("AGSGameMode::PostLogin End"));
}
