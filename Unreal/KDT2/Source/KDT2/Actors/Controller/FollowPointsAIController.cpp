// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/FollowPointsAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"

void AFollowPointsAIController::SetPointsAndMove(const TArray<FVector>& InPoints)
{
	Points = InPoints;
	MoveFromPoints();
}

void AFollowPointsAIController::BeginPlay()
{
	Super::BeginPlay();

	/*UClass* Class = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/Engine.Blueprint'/Game/KDT2/Blueprint/AI/BP_Path.BP_Path_C'"));

	AActor* Actor = UGameplayStatics::GetActorOfClass(this, Class);
	USplineComponent* SplineComponent = Actor->FindComponentByClass<USplineComponent>();

	const int32 PointNum = SplineComponent->GetNumberOfSplinePoints();
	Points.Reserve(PointNum);

	for (int32 i = 0; i < PointNum; ++i)
	{
		Points.Add(SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
	}

	if (PointNum > 0)
	{
		MoveFromPoints();
	}*/
}

void AFollowPointsAIController::MoveFromPoints()
{
	if (Points.Num() <= CurrentPointIndex)
	{
		return;
	}

	FVector& TargetLocation = Points[CurrentPointIndex];
	++CurrentPointIndex;
	MoveToLocation(TargetLocation);
}

void AFollowPointsAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.HasFlag(FPathFollowingResultFlags::UserAbort))
	{
		return;
	}
	if (!Result.IsSuccess())
	{
		ensure(false);
		return;
	}

	MoveFromPoints();
}
