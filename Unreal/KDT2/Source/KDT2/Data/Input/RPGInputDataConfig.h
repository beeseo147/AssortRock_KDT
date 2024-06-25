// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "RPGInputDataConfig.generated.h"

UCLASS()
class KDT2_API URPGInputDataConfig : public UObject
{
	GENERATED_BODY()
	
public:
	URPGInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	UInputAction* ZoomWheel = nullptr;
};
