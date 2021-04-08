// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	pWater = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	pLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	pSplash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	RootComponent = pBody;
	pWater->SetupAttachment(pBody);
	pLight->SetupAttachment(pBody);
	pSplash->SetupAttachment(pBody);

	pWater->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f));
	pLight->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	pSplash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WATER(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_02.SM_Plains_Castle_Fountain_02"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_SPLASH(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01"));

	if (SM_BODY.Succeeded())
		pBody->SetStaticMesh(SM_BODY.Object);

	if (SM_WATER.Succeeded())
		pWater->SetStaticMesh(SM_WATER.Object);

	if (PS_SPLASH.Succeeded())
		pSplash->SetTemplate(PS_SPLASH.Object);
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

