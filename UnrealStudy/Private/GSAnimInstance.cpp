// Fill out your copyright notice in the Description page of Project Settings.


#include "GSAnimInstance.h"

UGSAnimInstance::UGSAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Book/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
		AttackMontage = ATTACK_MONTAGE.Object;
}

void UGSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn) == false)
		return;

	if (IsDead == false)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		ACharacter* Character = Cast<ACharacter>(Pawn);
		if (Character)
			IsInAir = Character->GetMovementComponent()->IsFalling();
	}
}

void UGSAnimInstance::PlayAttackMontage()
{
	if (IsDead)
		return;

	Montage_Play(AttackMontage, 1.0f);
}

void UGSAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	if (IsDead)
		return;

	checkf(Montage_IsPlaying(AttackMontage), TEXT("Error"));
	Montage_JumpToSection(GetAttackMontageSelectionName(NewSection), AttackMontage);
}

FName UGSAnimInstance::GetAttackMontageSelectionName(int32 Section)
{
	checkf(FMath::IsWithinInclusive<int32>(Section, 1, 3), TEXT("Error"));
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void UGSAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UGSAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}
