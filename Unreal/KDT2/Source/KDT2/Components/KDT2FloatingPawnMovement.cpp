// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KDT2FloatingPawnMovement.h"

float GetAxisDeltaRotation(float InAxisRotationRate, float DeltaTime)
{
	// Values over 360 don't do anything, see FMath::FixedTurn. However we are trying to avoid giant floats from overflowing other calculations.
	return (InAxisRotationRate >= 0.f) ? FMath::Min(InAxisRotationRate * DeltaTime, 360.f) : 360.f;
}

void UKDT2FloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccelerationKDT2 = Velocity.GetSafeNormal();

	FRotator CurrentRotation = UpdatedComponent->GetComponentRotation(); // Normalized
	CurrentRotation.DiagnosticCheckNaN(TEXT("UKDT2FloatingPawnMovement::TickComponent(): CurrentRotation"));

	const float DeltaTimeOverride = DeltaTime * RotationSpeedRate;

	FRotator DeltaRot = GetDeltaRotation(DeltaTimeOverride);
	DeltaRot.DiagnosticCheckNaN(TEXT("UKDT2FloatingPawnMovement::TickComponent(): GetDeltaRotation"));

	FRotator DesiredRotation = ComputeOrientToMovementRotation(CurrentRotation, DeltaTimeOverride, DeltaRot);
	// Accumulate a desired new rotation.
	const float AngleTolerance = 1e-3f;

	if (!CurrentRotation.Equals(DesiredRotation, AngleTolerance))
	{
		if (FMath::IsNearlyZero(DeltaRot.Pitch))
		{
			DeltaRot.Pitch = 360.0;
		}
		if (FMath::IsNearlyZero(DeltaRot.Roll))
		{
			DeltaRot.Roll = 360.0;
		}

		// PITCH
		if (!FMath::IsNearlyEqual(CurrentRotation.Pitch, DesiredRotation.Pitch, AngleTolerance))
		{
			DesiredRotation.Pitch = FMath::FixedTurn(CurrentRotation.Pitch, DesiredRotation.Pitch, DeltaRot.Pitch);
		}

		// YAW
		if (!FMath::IsNearlyEqual(CurrentRotation.Yaw, DesiredRotation.Yaw, AngleTolerance))
		{
			DesiredRotation.Yaw = FMath::FixedTurn(CurrentRotation.Yaw, DesiredRotation.Yaw, DeltaRot.Yaw);
		}

		// ROLL
		if (!FMath::IsNearlyEqual(CurrentRotation.Roll, DesiredRotation.Roll, AngleTolerance))
		{
			DesiredRotation.Roll = FMath::FixedTurn(CurrentRotation.Roll, DesiredRotation.Roll, DeltaRot.Roll);
		}

		// Set the new rotation.
		DesiredRotation.DiagnosticCheckNaN(TEXT("UKDT2FloatingPawnMovement::TickComponent(): DesiredRotation"));
		MoveUpdatedComponent(FVector::ZeroVector, DesiredRotation, /*bSweep*/ false);
	}
}

FRotator UKDT2FloatingPawnMovement::GetDeltaRotation(float DeltaTime) const
{
	return FRotator(GetAxisDeltaRotation(RotationRate.Pitch, DeltaTime), GetAxisDeltaRotation(RotationRate.Yaw, DeltaTime), GetAxisDeltaRotation(RotationRate.Roll, DeltaTime));
}

FRotator UKDT2FloatingPawnMovement::ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const
{
	if (AccelerationKDT2.SizeSquared() < UE_KINDA_SMALL_NUMBER)
	{
		//// AI path following request can orient us in that direction (it's effectively an acceleration)
		//if (bHasRequestedVelocity && RequestedVelocity.SizeSquared() > UE_KINDA_SMALL_NUMBER)
		//{
		//	return RequestedVelocity.GetSafeNormal().Rotation();
		//}

		// Don't change rotation if there is no acceleration.
		return CurrentRotation;
	}

	// Rotate toward direction of acceleration.
	return AccelerationKDT2.GetSafeNormal().Rotation();
}
