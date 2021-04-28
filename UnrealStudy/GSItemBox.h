// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealStudy.h"
#include "GameFramework/Actor.h"
#include "GSItemBox.generated.h"

UCLASS()
class UNREALSTUDY_API AGSItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGSItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* pTrigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UStaticMeshComponent* pBox;

	UPROPERTY(EditInstanceOnly, Category = Box)
		TSubclassOf<class AGSWeapon> pWeaponItemClass;

	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* pEffect;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEffectFinishied(class UParticleSystemComponent* pSystem);
};
