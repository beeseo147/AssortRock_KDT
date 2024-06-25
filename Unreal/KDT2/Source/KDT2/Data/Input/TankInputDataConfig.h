// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "TankInputDataConfig.generated.h"

UCLASS()
class KDT2_API UTankInputDataConfig : public UObject
{
	GENERATED_BODY()

public:
	UTankInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	UInputAction* Zoom = nullptr;
	UInputAction* Fire = nullptr;
};
