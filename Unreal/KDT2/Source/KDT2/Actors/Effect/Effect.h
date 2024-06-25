// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Effect.generated.h"

USTRUCT()
struct FSound
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> Audio;

	UPROPERTY(EditAnywhere)
	float Multiplier = 1.f;
};
USTRUCT()
struct FParticle
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere)
	FVector ParticleScale = FVector::OneVector;
};

USTRUCT()
struct KDT2_API FEffectDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Actor")
	float InitialLifeSpan = 5.f;

	// Random으로 등록한 Audio중 하나가 재생 됩니다
	UPROPERTY(EditAnywhere, Category = "Effect|Audio")
	TArray<FSound> Audios;

	// 등록한 모든 Particle이 재생 됩니다
	UPROPERTY(EditAnywhere, Category = "Effect|Particle")
	TArray<FParticle> Particles;
};

UCLASS()
class KDT2_API AEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffect();
	void SetEffectData(const FEffectDataTableRow* InData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;

	TArray<UParticleSystemComponent*> Particles;

	FTimerHandle InitialLifeSpanTimer;
};
