// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AttackAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API UAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* SoundHit;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* SoundMiss;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UNiagaraSystem* ParticleHit;
	UPROPERTY(EditAnywhere, Category = "Particle")
	FVector ParticleScale = FVector::OneVector;
};
