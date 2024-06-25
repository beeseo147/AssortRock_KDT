// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actors/CameraManager/KDT2PlayerCameraManager.h"
#include "KDT2PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API AKDT2PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	friend class AKDT2Character;
	AKDT2PlayerController();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupInputComponent() override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY(Transient)
	URPGSaveGame* RPGSaveGame = nullptr;
};
