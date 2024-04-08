// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Coin/Coin.h"
//#include "Actors/GameState/CoinGameStateBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> Asset{ TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorHelp.EditorHelp'") };
	check(Asset.Succeeded());

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetStaticMesh(Asset.Object);
	//SetActorEnableCollision(false);
}

void ACoin::Active()
{
	ITriggerInterface::Active();
}

void ACoin::Inactive()
{
	ITriggerInterface::Inactive();
}

void ACoin::InTrigger()
{
	ITriggerInterface::InTrigger();

	bPandingKill = true;

	//ACoinGameStateBase* CoinGameState = Cast<ACoinGameStateBase>(GetWorld()->GetGameState());
	//const FCoinDataTableRow* Data = CoinDataTableRowHandle.GetRow<FCoinDataTableRow>(TEXT(""));
	//CoinGameState->GetCoin(Data);

	/*Owner->SetActorEnableCollision(false);

	if (CoinSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CoinSound, GetActorLocation());
	}*/

	auto TimerDelegate = [this]()
		{
			if (IsValid(this))
			{
				if (IsValid(Owner))
				{
					Owner->Destroy();
				}
				else
				{
					Destroy();
				}
			}
		};

	GetWorld()->GetTimerManager().SetTimer(CoinDestroyTimerHandle, TimerDelegate, 2.5f, false);
}

void ACoin::OutTrigger()
{
	ITriggerInterface::OutTrigger();
}

void ACoin::OnSubData(const FDataTableRowHandle& InSubData)
{
	ITriggerInterface::OnSubData(InSubData);
	const FCoinDataTableRow* Data = InSubData.GetRow<FCoinDataTableRow>(TEXT(""));
	if (!Data) { ensure(false); return; }

	CoinDataTableRowHandle = InSubData;
	StaticMeshComponent->SetStaticMesh(Data->StaicMesh);
	StaticMeshComponent->SetRelativeTransform(Data->StaticMeshTransform);
	//CoinSound = Data->CoinSound;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

}

//void ACoin::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//	Super::EndPlay(EndPlayReason);
//	GetWorld()->GetTimerManager().ClearTimer(CoinDestroyTimerHandle);
//}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPandingKill)
	{
		const double DeltaRotation = DeltaTime * RotationSpeed * 10.0;
		const FRotator Rotator{ 0.,DeltaRotation, 0. };
		StaticMeshComponent->AddLocalRotation(Rotator);

		const FVector Location = FVector::UpVector * DeltaTime * 100.0;
		StaticMeshComponent->AddRelativeLocation(Location);
	}
	else
	{
		const double DeltaRotation = DeltaTime * RotationSpeed;
		const FRotator Rotator{ 0.,DeltaRotation, 0. };
		StaticMeshComponent->AddLocalRotation(Rotator);
	}
}

