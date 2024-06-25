// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "WeaponInputDataConfig.generated.h"

UCLASS()
class KDT2_API UWeaponInputDataConfig : public UObject
{
	GENERATED_BODY()
	
public:
	UWeaponInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	UInputAction* Attack = nullptr;
};
