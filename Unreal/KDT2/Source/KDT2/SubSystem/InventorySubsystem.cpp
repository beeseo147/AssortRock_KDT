// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/InventorySubsystem.h"
#include "DataSubsystem.h"
#include "Misc/LocalSaveLoad/RPGSaveGame.h"

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UInventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UInventorySubsystem::Save(URPGSaveGame* SaveGame)
{
	SaveGame->InventoryItems.Empty();
	SaveGame->Weapon = FItemData();

	for (TSharedPtr<FItemData> It : Inventory)
	{
		if (It)
		{
			SaveGame->InventoryItems.Add(*It);
		}
	}

	if (Weapon)
	{
		SaveGame->Weapon = *Weapon;
	}

	/*SaveGame->InventoryItems.Empty();
	SaveGame->Weapon = FItemData();*/
}

void UInventorySubsystem::Load(class ARPGPlayerController* Controller, URPGSaveGame* SaveGame)
{
	for (FItemData& It : SaveGame->InventoryItems)
	{
		TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(It);
		MoveItemToInventory(NewItemData);
	}

	if (SaveGame->Weapon.ItemName != NAME_None)
	{
		TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(SaveGame->Weapon);
		Weapon = NewItemData;
		UItem* Item = SaveGame->Weapon.ItemFunctionClass->GetDefaultObject<UItem>();
		Item->UseItem(Controller, *Weapon);
	}
}

void UInventorySubsystem::MakeInventory()
{
	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	Inventory.SetNum(MaxInvenSize, false);

	/*for (int32 i = 0; i < 10; ++i)
	{
		AddItem(TEXT("Potion_HP"));
	}
	AddItem(TEXT("Hwando"));*/
}

void UInventorySubsystem::ClearInventory()
{
	Inventory.Empty();
	Weapon = nullptr;
}

void UInventorySubsystem::UnEquipWeapon(UInventoryUserWidget* Widget)
{
	UItem* Item = Weapon->ItemFunctionClass->GetDefaultObject<UItem>();
	Item->UnEquipItem(Cast<ARPGPlayerController>(Widget->GetOwningPlayer()), *Weapon);
	MoveItemToInventory(Weapon);
	Widget->FlushInven();
}

bool UInventorySubsystem::AddItem(const FName& InKey)
{
	const FItemData* Data = DataSubsystem->FindItem(InKey);
	if (!Data)
	{
		check(false);
		return false;
	}
	TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(*Data);
	NewItemData->ItemName = InKey;
	NewItemData->CurrentBundleCount = 1;

	return MoveItemToInventory(NewItemData);
}

bool UInventorySubsystem::MoveItemToInventory(TSharedPtr<FItemData>& InItem)
{
	for (uint32 i = 0; i < MaxInvenSize; ++i)
	{
		TSharedPtr<FItemData> ItemData = Inventory[i];
		if (ItemData == nullptr) { continue; }
		if (ItemData->ItemName != InItem->ItemName) { continue; }

		if (ItemData->MaxBundleCount > ItemData->CurrentBundleCount)
		{
			++ItemData->CurrentBundleCount;
			return true;
		}
	}

	bool bAdded = false;
	for (uint32 i = 0; i < MaxInvenSize; ++i)
	{
		if (Inventory[i] == nullptr)
		{
			Inventory[i] = InItem;
			bAdded = true;
			break;
		}
	}

	InItem = nullptr;

	return bAdded;
}

#include "UI/InventoryUserWidget.h"
#include "Actors/Controller/RPGPlayerController.h"

void UInventorySubsystem::UseItem(UInventoryUserWidget* Widget, uint32 InIndex)
{
	TWeakPtr<FItemData> ItemData = Inventory[InIndex];
	if (!ItemData.IsValid()) { return; }

	ARPGPlayerController* RPGPlayerController = Cast<ARPGPlayerController>(Widget->GetOwningPlayer());
	ensure(RPGPlayerController);

	UItem* Item = ItemData.Pin()->ItemFunctionClass->GetDefaultObject<UItem>();

	// interface로 번들 가능한 것에 대해서만 처리해도 되겠네요
	UItem_Weapon* ItemWeapon = Cast<UItem_Weapon>(Item);
	if (ItemWeapon)
	{
		Weapon = Inventory[InIndex];
		Item->UseItem(RPGPlayerController, *ItemData.Pin());
		Inventory[InIndex] = nullptr;
	}
	else
	{
		Item->UseItem(RPGPlayerController, *ItemData.Pin());
		--ItemData.Pin()->CurrentBundleCount;
	}

	if (ItemData.Pin()->CurrentBundleCount == 0)
	{
		Inventory[InIndex] = nullptr;
	}

	Widget->FlushInven();
}
