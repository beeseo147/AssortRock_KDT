// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/KDT2FloatingPawnMovement.h"
#include "Subsystem/DataSubsystem.h"
#include "MISC/MISC.h"
#include "Tank.generated.h"

UCLASS()
class KDT2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ZoomIn();
	void ZoomOut();
	void Fire();

protected:
	FName ProjectileName = TEXT("TankProjectile");
	const FProjectileDataTableRow* ProjectileRow;
	FTimerHandle FireTimerHandle;

protected:
	/*
	- BoxComponent
		- CameraSpringArmComponent
			- DefaultCamera
		- Body
		- TurretSpringArmComponent
			- Turret
			- Muzzle
				- ArrowComponent
				- ZoomCamera
	*/

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* DefaultCamera;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* TurretSpringArmComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Turret;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Muzzle;
	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* ZoomCamera;

protected:
	UPROPERTY(EditAnywhere)
	UKDT2FloatingPawnMovement* KDT2FloatingPawnMovement;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> UI;

	UPROPERTY()
	UUserWidget* ZoomInWidget;
};
