// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Controller/KDT2PlayerController.h"
#include "UI/RPGMainWidget.h"
#include "RPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API ARPGPlayerController : public AKDT2PlayerController
{
	GENERATED_BODY()
	friend class AKDT2Character;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds);

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess();

	void OnZoomWheel(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY()
	USpringArmComponent* PawnSpringArm = nullptr;
	float TargetArmLength = 500.f;

	UPROPERTY(BlueprintReadWrite)
	URPGMainWidget* RPGMainWidget = nullptr;
};
