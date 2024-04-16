// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "MISC/MISC.h"
#include "Components/KDT2FloatingPawnMovement.h"
#include "Actors/Interface/StatusInterface.h"
#include "Components/StatusComponent.h"
#include "Enemy.generated.h"

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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	UPROPERTY(EditAnywhere)
	UKDT2FloatingPawnMovement* KDT2FloatingPawnMovement;

	UPROPERTY(EditAnywhere)
	UStatusComponent* StatusComponent;
};
