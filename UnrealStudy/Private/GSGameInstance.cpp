// Fill out your copyright notice in the Description page of Project Settings.


#include "GSGameInstance.h"

UGSGameInstance::UGSGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/Book/GameData/ABCharacterData.ABCharacterData");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARACTER(*CharacterDataPath);
	if (DT_CHARACTER.Succeeded())
	{
		CharacterTable = DT_CHARACTER.Object;
	}
}

void UGSGameInstance::Init()
{
	Super::Init();
}

FGSCharacterData* UGSGameInstance::GetCharacterData(int32 level)
{
	return CharacterTable->FindRow<FGSCharacterData>(*FString::FromInt(level), TEXT(""));
}
