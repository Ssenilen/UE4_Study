// Fill out your copyright notice in the Description page of Project Settings.


#include "GSWeapon.h"

// Sets default values
AGSWeapon::AGSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = pWeapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Blade_BlackKnight(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));
	if (SK_Blade_BlackKnight.Succeeded())
	{
		pWeapon->SetSkeletalMesh(SK_Blade_BlackKnight.Object);
	}

	pWeapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AGSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

