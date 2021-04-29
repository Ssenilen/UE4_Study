// Fill out your copyright notice in the Description page of Project Settings.


#include "GSCharacterStatComponent.h"
#include "GSGameInstance.h"

// Sets default values for this component's properties
UGSCharacterStatComponent::UGSCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...

	Level = 1;
}

// Called when the game starts
void UGSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGSCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGSCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UGSCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto GameInstance = Cast<UGSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance)
	{
	 	CurrentStatData = GameInstance->GetCharacterData(NewLevel);
		if (CurrentStatData)
		{
			Level = NewLevel;
			SetHp(CurrentStatData->MaxHP);
			CurrentHp = CurrentStatData->MaxHP;
		}
		else
		{
			checkf(false, TEXT("Not Exist CurrentStatData"));
		}
	}
}

void UGSCharacterStatComponent::SetDamage(float NewDamage)
{
	checkf(CurrentStatData, TEXT("Error"));

	SetHp(FMath::Clamp<float>(CurrentHp - NewDamage, 0, CurrentStatData->MaxHP));
}

void UGSCharacterStatComponent::SetHp(float NewHP)
{
	CurrentHp = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHp < KINDA_SMALL_NUMBER)
	{
		CurrentHp = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UGSCharacterStatComponent::GetAttack()
{
	checkf(CurrentStatData, TEXT("Error"));
	return CurrentStatData->Attack;
}

float UGSCharacterStatComponent::GetHPRatio()
{
	checkf(CurrentStatData, TEXT("Error"));
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHp / CurrentStatData->MaxHP);
}
