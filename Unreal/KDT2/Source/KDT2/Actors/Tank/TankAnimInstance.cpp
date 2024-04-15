// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/TankAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

void UTankAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
	if (!Pawn) { return; }

	TurretRotation = Pawn->GetControlRotation();
}

void UTankAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!Pawn) { return; }

	FRotator Rotator = Pawn->GetControlRotation();
	TurretRotation = UKismetMathLibrary::RLerp(TurretRotation, FRotator(0., Rotator.Yaw, 0.), DeltaSeconds * 5.f, true);
}
