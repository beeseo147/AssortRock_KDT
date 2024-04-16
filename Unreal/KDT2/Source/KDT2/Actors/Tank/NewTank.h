// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/KDT2FloatingPawnMovement.h"
#include "Subsystem/Subsystem.h"
#include "MISC/MISC.h"
#include "Actors/Interface/TankInterface.h"
#include "NewTank.generated.h"

UCLASS()
class KDT2_API ANewTank : public APawn, public ITankInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANewTank();

public:
	// ITankInterface begin
	virtual void ZoomIn() override;
	virtual void ZoomOut() override;
	virtual void Fire() override;
	// ITankInterface end

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	FName ProjectileName = TEXT("TankProjectile");
	const FProjectileDataTableRow* ProjectileRow;
	FTimerHandle FireTimerHandle;

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* DefaultCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponent; //

	UPROPERTY(EditAnywhere)
	UCameraComponent* ZoomCamera;

protected:
	UPROPERTY(EditAnywhere)
	UKDT2FloatingPawnMovement* KDT2FloatingPawnMovement;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> UI;

	UPROPERTY(Transient)
	UUserWidget* ZoomInWidget;
};
