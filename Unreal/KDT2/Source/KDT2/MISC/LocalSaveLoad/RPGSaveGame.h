// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Data/Item/ItemData.h"
#include "RPGSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API URPGSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public: // Player
	UPROPERTY()
	FVector PlayerLocation;

	UPROPERTY()
	FRotator PlayerRotation;

public: // Controller
	UPROPERTY()
	FRotator ControllerRotation;

	UPROPERTY()
	float TargetArmLength;

public: // Inventory
	UPROPERTY()
	TArray<FItemData> InventoryItems;

	UPROPERTY()
	FItemData Weapon;
};
