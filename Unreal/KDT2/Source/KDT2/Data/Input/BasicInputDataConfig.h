// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BasicInputDataConfig.generated.h"

UCLASS()
class KDT2_API UBasicInputDataConfig : public UObject
{
	GENERATED_BODY()
	
public:
	UBasicInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	UInputAction* Move = nullptr;
	UInputAction* Look = nullptr;
};
