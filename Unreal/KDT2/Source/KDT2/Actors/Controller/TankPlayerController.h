// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Controller/KDT2PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class KDT2_API ATankPlayerController : public AKDT2PlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnZoomIn(const FInputActionValue& InputActionValue);
	void OnZoomOut(const FInputActionValue& InputActionValue);
	void OnFire(const FInputActionValue& InputActionValue);
};
