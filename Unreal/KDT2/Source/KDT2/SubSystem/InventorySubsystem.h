// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Data/Item/ItemData.h"
#include "Data/Item/Item.h"
#include "InventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API UInventorySubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
	friend class ARPGPlayerController;
	friend class UInventoryUserWidget;

protected:
	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection);

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize();

	void Save(class URPGSaveGame* SaveGame);
	void Load(class ARPGPlayerController* Controller, class URPGSaveGame* SaveGame);

	void MakeInventory();
	void ClearInventory();

	void UnEquipWeapon(class UInventoryUserWidget* Widget);

	bool AddItem(const FName& InKey);
	bool MoveItemToInventory(TSharedPtr<FItemData>& InItem);
	void UseItem(class UInventoryUserWidget* Widget, uint32 InIndex);

protected:
	const uint32 MaxInvenSize = 60;
	TArray<TSharedPtr<FItemData>> Inventory;

	TSharedPtr<FItemData> Weapon;

	class UDataSubsystem* DataSubsystem;
};
