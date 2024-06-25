// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "FollowPointsAIController.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API AFollowPointsAIController : public AAIController
{
	GENERATED_BODY()

public:
	void SetPointsAndMove(const TArray<FVector>& InPoints);

protected:
	virtual void BeginPlay() override;

	void MoveFromPoints();
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

protected:
	TArray<FVector> Points;
	int32 CurrentPointIndex = 0;
};
