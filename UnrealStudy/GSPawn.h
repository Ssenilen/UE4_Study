// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "GSPawn.generated.h"

UCLASS()
class UNREALSTUDY_API AGSPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGSPawn();

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent* pCapsule;
	
	UPROPERTY(VisibleAnywhere, Category = Visual)
		USkeletalMeshComponent* pSkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UFloatingPawnMovement* pMovement;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* pSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* pCamera;
};
