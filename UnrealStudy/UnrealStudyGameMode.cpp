// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealStudyGameMode.h"
#include "UnrealStudyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealStudyGameMode::AUnrealStudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
