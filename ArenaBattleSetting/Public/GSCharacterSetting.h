// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GSCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(config=UnrealStudy)
class ARENABATTLESETTING_API UGSCharacterSetting : public UObject
{
	GENERATED_BODY()
	
public:
	UGSCharacterSetting();

	UPROPERTY(config)
		TArray<FSoftObjectPath> CharacterAssets;
};
