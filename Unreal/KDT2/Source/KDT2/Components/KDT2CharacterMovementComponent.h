// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KDT2CharacterMovementComponent.generated.h"

UCLASS()
class KDT2_API UKDT2CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UKDT2CharacterMovementComponent();

protected:
	virtual void BeginPlay() override;

protected:
	/**
	 * Project a location to navmesh to find adjusted height.
	 * @param TestLocation		Location to project
	 * @param NavFloorLocation	Location on navmesh
	 * @return True if projection was performed (successfully or not)
	 */
	virtual bool FindNavFloor(const FVector& TestLocation, FNavLocation& NavFloorLocation) const override;
	virtual void PhysNavWalking(float deltaTime, int32 Iterations) override;
};
