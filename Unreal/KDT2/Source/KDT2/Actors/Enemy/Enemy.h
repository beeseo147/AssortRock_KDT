// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "MISC/MISC.h"
#include "Components/TimelineComponent.h"
#include "Components/KDT2FloatingPawnMovement.h"
#include "Components/StatusComponent.h"
#include "Components/WidgetComponent.h"
#include "AIController.h"
#include "PaperSpriteComponent.h"
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
	TSubclassOf<UAnimInstance> AnimClass;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	FTransform SkeletalMeshTransform;

	UPROPERTY(EditAnywhere, Category = "Enemy|AI")
	TSubclassOf<AAIController> AIClass = AAIController::StaticClass();

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.StatusDataTableRow"))
	FDataTableRowHandle StatusData;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT2.WeaponDataTableRow"))
	FDataTableRowHandle WeaponData;
};

UCLASS()
class KDT2_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	~AEnemy();
	virtual void SetEnemyData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void SetEnemyData(const FEnemyDataTableRow* InData);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
public:
	// PaperBurn Effect

	UFUNCTION()
	void OnPaperBurnEffect(float InPower);
	UFUNCTION()
	void OnPaperBurnEffectEnd();

	// PaperBurn Effect End

protected:
	virtual void PostInitializeComponents() override;
	virtual void PostRegisterAllComponents() override;
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
	UPaperSpriteComponent* PaperSpriteComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY(EditAnywhere)
	UChildActorComponent* WeaponChildActorComponent;

protected:
	UPROPERTY(EditAnywhere)
	UKDT2FloatingPawnMovement* KDT2FloatingPawnMovement;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* StatusWidget = nullptr;

	UPROPERTY(Transient)
	UStatusComponent* StatusComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UTimelineComponent* PaperBurnEffectTimelineComponent = nullptr;

protected:
	const FEnemyDataTableRow* EnemyDataTableRow = nullptr;
};
