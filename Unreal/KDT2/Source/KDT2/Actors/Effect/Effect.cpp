// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Effect/Effect.h"
#include "Actors/GameMode/TankGameModeBase.h"

// Sets default values
AEffect::AEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	//Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	//Particle2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle2"));

	SetRootComponent(AudioComponent);
	//Particle->SetupAttachment(AudioComponent);
	//Particle2->SetupAttachment(AudioComponent);
}

void AEffect::SetEffectData(const FEffectDataTableRow* InData)
{
	ensure(InData);
	GetWorld()->GetTimerManager().ClearTimer(InitialLifeSpanTimer);
	if (InData->InitialLifeSpan == 0.f)
	{
		ensure(false);
		return;
	}

	auto TimerDelegate = [this]()
		{
			ATankGameModeBase* GameMode = Cast<ATankGameModeBase>(GetWorld()->GetAuthGameMode());
			ensure(GameMode);
			GameMode->GetEffectPool().Delete(this);
		};

	GetWorld()->GetTimerManager().SetTimer(InitialLifeSpanTimer, TimerDelegate, InData->InitialLifeSpan, false);

	const int32 AudioCount = InData->Audios.Num();
	if (AudioCount >= 1)
	{
		const int32 RandomIndex = FMath::RandRange(0, AudioCount - 1);
		AudioComponent->Sound = InData->Audios[RandomIndex].Audio;
		AudioComponent->SetVolumeMultiplier(InData->Audios[RandomIndex].Multiplier);
		AudioComponent->Play();
	}

	const int32 ParticleCount = InData->Particles.Num();
	if (Particles.Num() < ParticleCount)
	{
		Particles.SetNum(ParticleCount);
		for (int32 i = 0; i < ParticleCount; ++i)
		{
			if (Particles[i] == nullptr)
			{
				FName UniqueName = MakeUniqueObjectName(this, UParticleSystemComponent::StaticClass());
				Particles[i] = NewObject<UParticleSystemComponent>(this, UniqueName);
				Particles[i]->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				Particles[i]->RegisterComponent();
			}
		}
	}

	for (int32 i = 0; i < ParticleCount; ++i)
	{
		Particles[i]->SetRelativeScale3D(InData->Particles[i].ParticleScale);
		Particles[i]->SetTemplate(InData->Particles[i].Particle);
	}
}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(InitialLifeSpanTimer);
}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

