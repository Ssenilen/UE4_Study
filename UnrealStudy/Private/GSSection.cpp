// Fill out your copyright notice in the Description page of Project Settings.


#include "GSSection.h"
#include "GSCharacter.h"
#include "GSItemBox.h"

// Sets default values
AGSSection::AGSSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bNoBattle = false;
	EnemySpawnTime = 2.0f;
	ItemBoxSpawnTime = 5.0f;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/Book/StaticMesh/SM_SQUARE.SM_SQUARE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(*AssetPath);
	if (SM_SQUARE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_SQUARE.Object);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	Trigger->SetCollisionProfileName(TEXT("GSTrigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGSSection::OnTriggerBeginOverlap);

	FString GateAssetPath = TEXT("/Game/Book/StaticMesh/SM_GATE.SM_GATE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GATE(*GateAssetPath);
	if (SM_GATE.Succeeded())
	{
		static FName GateSockets[] = { {TEXT("+XGate")}, {TEXT("-XGate")} ,{TEXT("+YGate")} ,{TEXT("-YGate")} };

		for (FName GateSocket : GateSockets)
		{
			if (Mesh->DoesSocketExist(GateSocket))
			{
				UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
				NewGate->SetStaticMesh(SM_GATE.Object);
				NewGate->SetupAttachment(RootComponent, GateSocket);
				NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
				GateMeshes.Add(NewGate);

				UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("TRIGGER")));
				NewGateTrigger->SetBoxExtent(FVector(100.f, 100.0f, 300.0f));
				NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
				NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
				NewGateTrigger->SetCollisionProfileName(TEXT("GSTrigger"));
				GateTriggers.Add(NewGateTrigger);

				NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGSSection::OnGateTriggerBeginOverlap);
				NewGateTrigger->ComponentTags.Add(GateSocket);
			}
		}

		bNoBattle = false;
	}


}

// Called when the game starts or when spawned
void AGSSection::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void AGSSection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ESectionState::READY:
	{
		Trigger->SetCollisionProfileName(TEXT("GSTrigger"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}
		OperateGates(true);
		break;
	}
	case ESectionState::BATTLE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}
		OperateGates(false);

		GetWorld()->GetTimerManager().SetTimer(SpawnNpcTimerHandle, FTimerDelegate::CreateUObject(this, &AGSSection::OnNPCSpawn), EnemySpawnTime, false);
		GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]() {
			FVector2D RandXY = FMath::RandPointInCircle(600.0f);
			GetWorld()->SpawnActor<AGSItemBox>(GetActorLocation() + FVector(RandXY, 30.0f), FRotator::ZeroRotator);
		}), ItemBoxSpawnTime, false);

		break;
	}
	case ESectionState::COMPLETE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("GSTrigger"));
		}
		OperateGates(true);
		break;
	}
	}
}

void AGSSection::OperateGates(bool bOpen)
{
	for (UStaticMeshComponent* Gate : GateMeshes)
	{
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

void AGSSection::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentState == ESectionState::READY)
	{
		SetState(ESectionState::BATTLE);
	}
}

void AGSSection::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	check(OverlappedComponent->ComponentTags.Num() == 1);
	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));

	if (!Mesh->DoesSocketExist(SocketName))
		return;

	FVector NewLocation = Mesh->GetSocketLocation(SocketName);

	TArray<FOverlapResult> OverlapResult;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);

	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResult,
		NewLocation,
		FQuat::Identity,
		ObjectQueryParam,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam);

	if (!bResult)
	{
		AGSSection* NewSection = GetWorld()->SpawnActor<AGSSection>(NewLocation, FRotator::ZeroRotator);
	}
}

void AGSSection::OnNPCSpawn()
{
	GetWorld()->SpawnActor<AGSCharacter>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
}

// Called every frame
void AGSSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGSSection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

