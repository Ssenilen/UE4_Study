// Fill out your copyright notice in the Description page of Project Settings.


#include "GSPawn.h"

// Sets default values
AGSPawn::AGSPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	pSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETALMESH"));
	pMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = pCapsule;

	// Movecomponent는 액터에 직접 부착되므로 SetupAttachment 해줄 필요 없음.
	pSkeletalMesh->SetupAttachment(pCapsule);
	pSpringArm->SetupAttachment(pCapsule);
	pCamera->SetupAttachment(pSpringArm);

	pCapsule->SetCapsuleHalfHeight(88.0f);
	pCapsule->SetCapsuleRadius(34.0f);
	pSkeletalMesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	pSpringArm->TargetArmLength = 400.0f;
	pSpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		pSkeletalMesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	pSkeletalMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		pSkeletalMesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}
}

void AGSPawn::UpDown(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AGSPawn::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

// Called when the game starts or when spawned
void AGSPawn::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AGSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGSPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	debugf(TEXT("AGSPawn::PostInitializeComponents"));
}

void AGSPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	debugf(TEXT("AGSPawn::PossessdBy"));
}

// Called to bind functionality to input
void AGSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AGSPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AGSPawn::LeftRight);
}

