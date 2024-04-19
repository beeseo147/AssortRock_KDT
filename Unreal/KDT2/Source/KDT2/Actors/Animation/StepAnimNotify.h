// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "StepAnimNotify.generated.h"

USTRUCT()
struct FFootStepInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Sound")
	TArray<USoundBase*> Sounds;

	UPROPERTY(EditAnywhere, Category = "Sound")
	float VolumeMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UNiagaraSystem* Particle;
	UPROPERTY(EditAnywhere, Category = "Particle")
	FVector ParticleScale = FVector::OneVector;
};

// UAnimNotify_PlayNiagaraEffect
/**
 *
 */
UCLASS()
class KDT2_API UStepAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	void Play(USkeletalMeshComponent* MeshComp, const FFootStepInfo& InFootStepInfo);

protected:
	UPROPERTY(EditAnywhere)
	FFootStepInfo FootStepInfo_Default;
	UPROPERTY(EditAnywhere)
	FFootStepInfo FootStepInfo_Water;
};
