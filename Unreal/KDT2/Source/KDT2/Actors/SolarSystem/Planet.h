// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planet.generated.h"

USTRUCT(BlueprintType)
struct FSatellite
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Axis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* ChildActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double RotationSpeed = 90.0;
};


UCLASS()
class KDT2_API APlanet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlanet();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* PlanetAxis;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* PlanetStaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* CloudAxis;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* CloudStaticMeshComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* newPlanetAxis;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* newPlanetStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double PlanetRotationSpeed = 90.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double CloudRotationSpeed = 180.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCloud = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSatellite> SatelliteArray;
	

protected:
	UPROPERTY()
	UMaterialInstanceDynamic* PlanetMaterialInstanceDynamic;
};
