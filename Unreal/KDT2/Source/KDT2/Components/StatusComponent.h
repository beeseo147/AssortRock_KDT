// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

USTRUCT()
struct KDT2_API FStatusDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float HP = 10;

	FStatusDataTableRow();
	TSubclassOf<class UStatusComponent> StatusComponentClass;
};

UCLASS(ClassGroup = (Custom)/*, meta=(BlueprintSpawnableComponent)*/)
class KDT2_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void SetStatusData(const FStatusDataTableRow* InData);

public:
	// Sets default values for this component's properties
	UStatusComponent();

	virtual float ProcessDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	float HP = 10;

protected:
	const FStatusDataTableRow* StatusDataTableRow = nullptr;
};

USTRUCT()
struct KDT2_API FStatus2DataTableRow : public FStatusDataTableRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MP = 10;

	FStatus2DataTableRow();
};

UCLASS(ClassGroup = (Custom)/*, meta=(BlueprintSpawnableComponent)*/)
class KDT2_API UStatusComponent2 : public UStatusComponent
{
	GENERATED_BODY()

public:
	virtual void SetStatusData(const FStatusDataTableRow* InData) override
	{
		Super::SetStatusData(InData);
		const FStatus2DataTableRow* Status = (const FStatus2DataTableRow*)InData;

		MP = Status->MP;
	}
	virtual float ProcessDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
	{
		return Super::ProcessDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}

protected:
	UPROPERTY(EditAnywhere)
	float MP = 10;
};