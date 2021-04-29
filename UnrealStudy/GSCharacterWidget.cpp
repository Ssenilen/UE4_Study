// Fill out your copyright notice in the Description page of Project Settings.


#include "GSCharacterWidget.h"
#include "GSCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UGSCharacterWidget::BindCharacterStat(class UGSCharacterStatComponent* NewCharacterStat)
{
	checkf(NewCharacterStat, TEXT("Error"));

	CurrentCharacterStat = NewCharacterStat;
	
	NewCharacterStat->OnHPChanged.AddUObject(this, &UGSCharacterWidget::UpdateHPWidget);

}

void UGSCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName("PB_HPBar"));
	UpdateHPWidget();
}

void UGSCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid() && HPProgressBar)
	{
		HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	}
}
