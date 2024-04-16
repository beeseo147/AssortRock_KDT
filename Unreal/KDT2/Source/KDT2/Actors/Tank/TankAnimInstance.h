// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TankAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class KDT2_API UTankAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	FRotator TurretRotation;

	double Speed = 0;
	UPROPERTY(BlueprintReadOnly)
	FRotator WheelRotation;
	UPROPERTY(BlueprintReadOnly)
	double TracksV = 0.;

	APawn* Pawn;
};
