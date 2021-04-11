// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/PlayerController.h"
#include "GSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AGSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* PawnToPossess) override;
};
