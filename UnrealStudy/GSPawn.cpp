// Fill out your copyright notice in the Description page of Project Settings.


#include "GSPawn.h"

// Sets default values
AGSPawn::AGSPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

