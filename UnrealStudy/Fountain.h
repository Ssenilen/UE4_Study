// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class UNREALSTUDY_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* pBody;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* pWater;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* pSplash;

	UPROPERTY(VisibleAnywhere)
		UPointLightComponent* pLight;

	UPROPERTY(VisibleAnywhere)
		URotatingMovementComponent* pMovement;

	UPROPERTY(EditAnywhere, Category=ID)
		int32 id;

private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
		float rotateSpeed;
};
