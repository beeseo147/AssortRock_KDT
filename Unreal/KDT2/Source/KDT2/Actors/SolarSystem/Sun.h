// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Sun.generated.h"

UCLASS()
class KDT2_API ASun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASun();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSunPower(float InPower);

private:
	UPROPERTY(EditAnywhere)//UStaticMeshComponent를 언리얼 에디터에서 수정가능하게 바꾼다.
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UTimelineComponent* SunPowerTimelineComponent = nullptr;

	UPROPERTY()
	UMaterialInstanceDynamic* MID = nullptr;

	static inline UMaterial* SunMaterial = nullptr;
};
