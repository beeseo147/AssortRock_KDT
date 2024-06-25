// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.generated.h"

class ARPGPlayerController;
struct FItemData;

UCLASS()
class UItem : public UObject
{
	GENERATED_BODY()

	friend class UInventorySubsystem;

protected:
	virtual void UseItem(ARPGPlayerController* Controller, FItemData& ItemData)
	{
		int a = 0;
	}
	virtual void UnEquipItem(ARPGPlayerController* Controller, FItemData& ItemData) {}
};

UCLASS()
class UItem_Potion : public UItem
{
	GENERATED_BODY()
	friend class UInventorySubsystem;
protected:
	virtual void UseItem(ARPGPlayerController* Controller, FItemData& ItemData);
};

UCLASS()
class UItem_Weapon : public UItem
{
	GENERATED_BODY()
	friend class UInventorySubsystem;
protected:
	virtual void UseItem(ARPGPlayerController* Controller, FItemData& ItemData);
	virtual void UnEquipItem(ARPGPlayerController* Controller, FItemData& ItemData);
};