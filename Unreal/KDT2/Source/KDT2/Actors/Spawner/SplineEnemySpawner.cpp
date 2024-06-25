// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawner/SplineEnemySpawner.h"
#include "Actors/Enemy/Enemy.h"
#include "Actors/Controller/FollowPointsAIController.h"

// Sets default values
ASplineEnemySpawner::ASplineEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("SplinePath"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(SplinePath);
	Mesh->SetupAttachment(SplinePath);
}

void ASplineEnemySpawner::StartSpawn(UEnemySpawnDataAsset* NewEnemySpawnDataAsset)
{
	if (!NewEnemySpawnDataAsset)
	{
		ensure(false);
		return;
	}

	EnemySpawnDataAsset = NewEnemySpawnDataAsset;
	if (EnemySpawnDataAsset->EnemySpawnInfoArray.IsEmpty())
	{
		check(false);
		return;
	}

	Spawn();
}

void ASplineEnemySpawner::Spawn()
{
	if (EnemySpawnDataAsset->EnemySpawnInfoArray.Num() == CurrentSpawnIndex)
	{
		Destroy();
		return;
	}

	FEnemySpawnInfo& EnemySpawnInfo = EnemySpawnDataAsset->EnemySpawnInfoArray[CurrentSpawnIndex];
	++CurrentSpawnIndex;
	Spawn(EnemySpawnInfo, EnemySpawnInfo.SpawnCount);
}

void ASplineEnemySpawner::Spawn(FEnemySpawnInfo& InEnemySpawnInfo, const uint32 InRemainCount)
{
	GetWorldTimerManager().SetTimer(SpawnDelayTimer, [this, &InEnemySpawnInfo, InRemainCount]()
		{
			{
				UE_LOG(LogTemp, Warning, TEXT("Spawn! %s"), *InEnemySpawnInfo.Enemy.RowName.ToString());

				FEnemyDataTableRow* EnemyDataTableRow = InEnemySpawnInfo.Enemy.GetRow<FEnemyDataTableRow>(TEXT(""));
				const FVector EnemySkeletalMeshLocation = EnemyDataTableRow->SkeletalMeshTransform.GetLocation();
				const FVector NewLocation = GetActorLocation() + FVector(0., 0., -EnemySkeletalMeshLocation.Z);
				const FTransform SpawnTransform = FTransform(GetActorRotation(), NewLocation);
				AEnemy* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemy>(AEnemy::StaticClass(), SpawnTransform, nullptr, nullptr,
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				NewEnemy->SetEnemyData(InEnemySpawnInfo.Enemy);
				NewEnemy->FinishSpawning(SpawnTransform, true);

				{
					TArray<FVector> Points;
					const int32 PointNum = SplinePath->GetNumberOfSplinePoints();
					Points.Reserve(PointNum);

					for (int32 i = 0; i < PointNum; ++i)
					{
						Points.Add(SplinePath->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
					}

					AFollowPointsAIController* AIController = Cast<AFollowPointsAIController>(NewEnemy->GetController());
					if (AIController)
					{
						AIController->SetPointsAndMove(Points);
					}
					else
					{
						ensure(false);
					}
				}
			}

			const uint32 NewRemainCount = InRemainCount - 1;
			if (NewRemainCount == 0)
			{
				Spawn();
			}
			else
			{
				Spawn(InEnemySpawnInfo, NewRemainCount);
			}

		}, InEnemySpawnInfo.SpawnDelay, false);
}

// Called when the game starts or when spawned
void ASplineEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (EnemySpawnDataAsset)
	{
		StartSpawn(EnemySpawnDataAsset);
	}
}

void ASplineEnemySpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearTimer(SpawnDelayTimer);
}

// Called every frame
void ASplineEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

