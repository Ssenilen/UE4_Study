// Fill out your copyright notice in the Description page of Project Settings.


#include "GSItemBox.h"
#include "GSCharacter.h"
#include "GSWeapon.h"

// Sets default values
AGSItemBox::AGSItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	pTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	pBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	pEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = pTrigger;
	pBox->SetupAttachment(RootComponent);
	pEffect->SetupAttachment(RootComponent);

	pTrigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_BOX.Succeeded())
	{
		pBox->SetStaticMesh(SM_BOX.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (PS_CHESTOPEN.Succeeded())
	{
		pEffect->SetTemplate(PS_CHESTOPEN.Object);
		pEffect->bAutoActivate = false;
	}

	pBox->SetRelativeLocation(FVector(0.0f, -3.5f, 0.0f));

	pTrigger->SetCollisionProfileName(TEXT("GSItemBox"));
	pBox->SetCollisionProfileName(TEXT("NoCollision"));

	pWeaponItemClass = AGSWeapon::StaticClass();
}

// Called when the game starts or when spawned
void AGSItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGSItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	pTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGSItemBox::OnCharacterOverlap);
}

// Called every frame
void AGSItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGSItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGSCharacter* pChracter = Cast<AGSCharacter>(OtherActor);
	if (pChracter && pWeaponItemClass)
	{
		if (pChracter->CanSetWeapon())
		{
			AGSWeapon* pNewWeapon = GetWorld()->SpawnActor<AGSWeapon>(pWeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			pChracter->SetWeapon(pNewWeapon);
			pEffect->Activate(true);
			pBox->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			pEffect->OnSystemFinished.AddDynamic(this, &AGSItemBox::OnEffectFinishied);
		}
		else
		{
			debugf(TEXT("Already have weapon."));
		}
	}
}

void AGSItemBox::OnEffectFinishied(UParticleSystemComponent* pSystem)
{
	Destroy();
}

