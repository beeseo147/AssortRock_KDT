// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "KDT2FloatingPawnMovement.generated.h"

/**
 *
 */
UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class KDT2_API UKDT2FloatingPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Returns how far to rotate character during the time interval DeltaTime. */
	virtual FRotator GetDeltaRotation(float DeltaTime) const;

	/**
	  * Compute a target rotation based on current movement. Used by PhysicsRotation() when bOrientRotationToMovement is true.
	  * Default implementation targets a rotation based on Acceleration.
	  *
	  * @param CurrentRotation	- Current rotation of the Character
	  * @param DeltaTime		- Time slice for this movement
	  * @param DeltaRotation	- Proposed rotation change based simply on DeltaTime * RotationRate
	  *
	  * @return The target rotation given current movement.
	  */
	virtual FRotator ComputeOrientToMovementRotation(const FRotator& CurrentRotation, float DeltaTime, FRotator& DeltaRotation) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeedRate = 1.;

	/**
	 * Current acceleration vector (with magnitude).
	 * This is calculated each update based on the input vector and the constraints of MaxAcceleration and the current movement mode.
	 */
	 //UPROPERTY()
	FVector AccelerationKDT2;

	FRotator RotationRate = FRotator(0., 360., 0.);
};
