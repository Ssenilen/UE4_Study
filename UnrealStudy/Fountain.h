// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
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

	UPROPERTY(EditAnywhere, Category=ID)
		int32 id;
};
