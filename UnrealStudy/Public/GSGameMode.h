// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/GameModeBase.h"
#include "GSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AGSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGSGameMode();

	void PostLogin(APlayerController* NewPlayer) override;
};
