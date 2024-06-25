// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "SplineEnemySpawner.generated.h"

USTRUCT()
struct FEnemySpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (UIMin = 0.1f, ClampMin = 0.1f))
	float SpawnDelay = 1.f;

	UPROPERTY(EditAnywhere)
	uint32 SpawnCount = 1;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.EnemyDataTableRow"))
	FDataTableRowHandle Enemy;
};

UCLASS(BlueprintType)
class UEnemySpawnDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FEnemySpawnInfo> EnemySpawnInfoArray;
};

UCLASS()
class KDT2_API ASplineEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineEnemySpawner();

	UFUNCTION(BlueprintCallable)
	void StartSpawn(UEnemySpawnDataAsset* NewEnemySpawnDataAsset);

protected:
	void Spawn();
	void Spawn(FEnemySpawnInfo& InEnemySpawnInfo, const uint32 InRemainCount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	// Spline Point의 위치만 사용해서 이동합니다.
	// Spline 경로는 무시합니다
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* SplinePath;

	int32 CurrentSpawnIndex = 0;
	FTimerHandle SpawnDelayTimer;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemySpawnDataAsset* EnemySpawnDataAsset;
};
