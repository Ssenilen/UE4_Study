// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "GSGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGSCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGSCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 DropExp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 NextExp;
};


UCLASS()
class UNREALSTUDY_API UGSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGSGameInstance();

	virtual void Init() override;
	FGSCharacterData* GetCharacterData(int32 level);

	FStreamableManager StreamableManager;

private:
	UPROPERTY()
		class UDataTable* CharacterTable;
};
