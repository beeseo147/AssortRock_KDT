// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "MISC/MISC.h"
#include "Components/KDT2FloatingPawnMovement.h"
#include "Components/StatusComponent.h"
#include "Enemy.generated.h"

USTRUCT()
struct KDT2_API FEnemyDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FVector BoxExtent;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FTransform SkeletalMeshTransform;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.StatusDataTableRow"))
	FDataTableRowHandle StatusData;
};

UCLASS()
class KDT2_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	/** Name of the Status component. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static inline FName StatusComponentName = (TEXT("StatusComponent"));

public:
	// Sets default values for this pawn's properties
	AEnemy();
	~AEnemy();
	virtual void SetEnemyData(const FEnemyDataTableRow* InData);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.EnemyDataTableRow"))
	FDataTableRowHandle DataTableRowHandle;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	UPROPERTY(EditAnywhere)
	UKDT2FloatingPawnMovement* KDT2FloatingPawnMovement;

	UPROPERTY(Transient)
	UStatusComponent* StatusComponent = nullptr;

protected:
	const FEnemyDataTableRow* EnemyDataTableRow = nullptr;
};
