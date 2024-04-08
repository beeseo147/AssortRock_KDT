// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Data/Trigger/TriggerDataTableRow.h"
#include "MyTriggerBase.generated.h"

UCLASS()
class KDT2_API AMyTriggerBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyTriggerBase();

	UFUNCTION()
	void OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	AActor* GetTriggerOjbect();
	void Active();
	void Inactive();
	void InTrigger();
	void OutTrigger();

protected:
	virtual void PreRegisterAllComponents() override;
	virtual void PostRegisterAllComponents() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.TriggerDataTableRow"))
	FDataTableRowHandle TriggerObjectData;

	const FTriggerDataTableRow* TriggerDataTableRow;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* ActiveRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Trigger;

	UPROPERTY()
	UChildActorComponent* TriggerObject;
};
