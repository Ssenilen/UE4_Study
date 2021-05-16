// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/Character.h"
#include "GSCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class UNREALSTUDY_API AGSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PossessedBy(AController* NewController) override;

	bool CanSetWeapon();
	void SetWeapon(class AGSWeapon* pNewWeapon);

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		AGSWeapon* pCurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* pSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* pCamera;

	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UGSCharacterStatComponent* pCharacterStat;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* pHPBarWidget;

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

protected:
	enum class EControlMode
	{
		GTA,
		DIABLO,
		NPC,
	};

	void SetControlMode(EControlMode ControlMode);
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;
	float ModeChangeTime = 0.0f;
	float TimeCheck = 0.0f;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void ViewChange();
	void AttackCheck();

	void AttackStartComboState();
	void AttackEndComboState();

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	//UPROPERTY(VisibleAnywhere, Category = Weapon)
	//	USkeletalMeshComponent* pWeapon;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo;

	UPROPERTY()
		class UGSAnimInstance* AnimInstance;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;

};
