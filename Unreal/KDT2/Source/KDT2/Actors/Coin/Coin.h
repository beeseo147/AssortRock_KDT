// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Trigger/TriggerInterface.h"
#include "Coin.generated.h"

USTRUCT()
struct KDT2_API FCoinDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaicMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform StaticMeshTransform;

	UPROPERTY(EditAnywhere)
	USoundBase* CoinSound;

	UPROPERTY(EditAnywhere)
	uint32 Point = 1;
};

UCLASS()
class KDT2_API ACoin : public AActor, public ITriggerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoin();

	virtual void Active() override;
	virtual void Inactive() override;
	virtual void InTrigger() override;
	virtual void OutTrigger() override;

	virtual void OnSubData(const FDataTableRowHandle& InSubData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	FDataTableRowHandle CoinDataTableRowHandle;

	//FTimerHandle CoinDestroyTimerHandle;

protected:
	bool bPandingKill = false;

	/*UPROPERTY(EditAnywhere)
	double RotationSpeed = 45.0;*/

	/*UPROPERTY(EditAnywhere)
	USoundBase* CoinSound;*/
};
