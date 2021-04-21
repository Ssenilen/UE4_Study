// Fill out your copyright notice in the Description page of Project Settings.


#include "GSCharacter.h"
#include "GSAnimInstance.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGSCharacter::AGSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPIRNGARM"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	pSpringArm->SetupAttachment(GetCapsuleComponent());
	pCamera->SetupAttachment(pSpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	pSpringArm->TargetArmLength = 400.0f;
	pSpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	ModeChangeTime = 3.0f;
	IsAttacking = false;

	MaxCombo = 3;
	AttackEndComboState();

	GetCharacterMovement()->JumpZVelocity = 800.0f;

	SetControlMode(EControlMode::DIABLO);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("GSCharacter"));

	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

// Called when the game starts or when spawned
void AGSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TimeCheck -= DeltaTime;
	if (TimeCheck > 0.0f)
	{
		pSpringArm->SetRelativeRotation(FMath::RInterpTo(pSpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));
	}

	if (CurrentControlMode == EControlMode::DIABLO)
	{
		if (DirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
	}

	pSpringArm->TargetArmLength = FMath::FInterpTo(pSpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
}

// Called to bind functionality to input
void AGSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AGSCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AGSCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AGSCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AGSCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AGSCharacter::ViewChange);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AGSCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AGSCharacter::Attack);
}

void AGSCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UGSAnimInstance>(GetMesh()->GetAnimInstance());
	checkf(AnimInstance);
	
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AGSCharacter::OnAttackMontageEnded);

		AnimInstance->OnNextAttackCheck.AddLambda([this]() {
			CanNextCombo = false;

			if (IsComboInputOn)
			{
				AttackStartComboState();
				AnimInstance->JumpToAttackMontageSection(CurrentCombo);
			}
		});
	}

	AnimInstance->OnAttackHitCheck.AddUObject(this, &AGSCharacter::AttackCheck);
}

float AGSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	debugf(TEXT("Actor %s took Damage: %f"), *GetName(), FinalDamage);

	if (FinalDamage > 0.0f)
	{
		AnimInstance->SetDeadAnim();
		SetActorEnableCollision(false);
	}

	return FinalDamage;
}

void AGSCharacter::SetControlMode(EControlMode ControlMode)
{
	CurrentControlMode = ControlMode;

	if (ControlMode == EControlMode::GTA)
	{
		//pSpringArm->TargetArmLength = 450.0f;
		//pSpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		pSpringArm->bUsePawnControlRotation = true;
		pSpringArm->bInheritPitch = true;
		pSpringArm->bInheritYaw = true;
		pSpringArm->bInheritRoll = true;
		pSpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		ArmLengthTo = 450.0f;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

		pSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmRotationTo = GetControlRotation();
		TimeCheck = ModeChangeTime;
	}
	else if (ControlMode== EControlMode::DIABLO)
	{
		//pSpringArm->TargetArmLength = 800.0f;
		//pSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		pSpringArm->bUsePawnControlRotation = false;
		pSpringArm->bInheritPitch = false;
		pSpringArm->bInheritYaw = false;
		pSpringArm->bInheritRoll = false;
		pSpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		ArmLengthTo = 800.0;

		pSpringArm->SetRelativeRotation(GetControlRotation());
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		TimeCheck = ModeChangeTime;
	}
}

void AGSCharacter::UpDown(float NewAxisValue)
{
	if (CurrentControlMode == EControlMode::GTA)
	{
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
	}
	else if (CurrentControlMode == EControlMode::DIABLO)
	{
		DirectionToMove.X = NewAxisValue;
	}
}

void AGSCharacter::LeftRight(float NewAxisValue)
{
	if (CurrentControlMode == EControlMode::GTA)
	{
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
	}
	else if (CurrentControlMode == EControlMode::DIABLO)
	{
		DirectionToMove.Y = NewAxisValue;
	}
}

void AGSCharacter::LookUp(float NewAxisValue)
{
	if (CurrentControlMode == EControlMode::GTA)
	{
		AddControllerPitchInput(NewAxisValue);
	}
}

void AGSCharacter::Turn(float NewAxisValue)
{
	if (CurrentControlMode == EControlMode::GTA)
	{
		AddControllerYawInput(NewAxisValue);
	}
}

void AGSCharacter::ViewChange()
{
	if (CurrentControlMode == EControlMode::DIABLO)
	{
		SetControlMode(EControlMode::GTA);
		//GetController()->SetControlRotation(GetActorRotation());
	}
	else if (CurrentControlMode == EControlMode::GTA)
	{
		SetControlMode(EControlMode::DIABLO);
		//GetController()->SetControlRotation(pSpringArm->GetRelativeRotation());
	}
}

void AGSCharacter::Attack()
{
	if (IsAttacking)
	{
		if (CanNextCombo)
			IsComboInputOn = true;
	}
	else
	{
		checkf(CurrentCombo == 0);
		AttackStartComboState();
		AnimInstance->PlayAttackMontage();
		AnimInstance->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}
}

void AGSCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);


#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 3.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif
	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			debugf(TEXT("Hit Success!"));

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}

void AGSCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	checkf(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void AGSCharacter::AttackEndComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;
	CurrentCombo = 0;
}

void AGSCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	checkf(IsAttacking && CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
}


