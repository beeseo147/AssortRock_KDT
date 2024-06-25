// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryUserWidget.h"
#include "Subsystem/Subsystem.h"
#include "InventoryItemUserWidget.h"

void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InvenSize > 0)
	{
		FlushInven();
		return;
	}

	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	InventorySubsystem = ULocalPlayer::GetSubsystem<UInventorySubsystem>(LocalPlayer);
	InvenSize = InventorySubsystem->Inventory.Num();
	Items.Reserve(InvenSize);
	
	// 게임에서 참조된 적이 없어서 로드가 안됨
	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/RPG/UI/Backpack/UI_InventoryItem.UI_InventoryItem_C'"),
		nullptr, LOAD_None, nullptr);
	UClass* InventoryItemWidgetClass = FindObject<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/RPG/UI/Backpack/UI_InventoryItem.UI_InventoryItem_C'"));

	// Weapon
	{
		Weapon->ItemBtnHovered.BindUFunction(this, TEXT("OnWeaponBtnHovered"));
		Weapon->ItemBtnClicked.BindUFunction(this, TEXT("OnWeaponBtnClicked"));
	}

	int32 Col = 6;
	int32 Row = InvenSize / Col;

	for (int32 i = 0; i < Row; ++i)
	{
		for (int32 k = 0; k < Col; ++k)
		{
			UInventoryItemUserWidget* Widget = Cast<UInventoryItemUserWidget>(CreateWidget(this, InventoryItemWidgetClass));
			ensure(Widget);

			Widget->ItemIndex = k + i * Col;

			Widget->ItemBtnHovered.BindLambda(
				[this](UInventoryItemUserWidget* ItemWidget)
				{
					const uint32 Index = ItemWidget->ItemIndex;
					LastHoveredIndex = Index;
					SetItemDesc(Index);
				}
			);

			Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));

			Items.Add(Widget);
			InventoryPanel->AddChildToUniformGrid(Widget, i, k);
		}
	}

	FlushInven();
}

void UInventoryUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInventoryUserWidget::FlushInven()
{
	if (InventorySubsystem->Weapon)
	{
		UTexture2D* Texture = InventorySubsystem->Weapon->ItemImage;
		Weapon->ItemImage->SetBrushFromTexture(Texture, false);
	}
	else
	{
		Weapon->ItemImage->SetBrushFromTexture(nullptr, false);
	}

	for (int32 i = 0; i < InvenSize; ++i)
	{
		if (InventorySubsystem->Inventory[i] == nullptr)
		{
			Items[i]->ItemImage->SetBrushFromTexture(nullptr, false);
			continue;
		}

		UTexture2D* Texture = InventorySubsystem->Inventory[i]->ItemImage;
		Items[i]->ItemImage->SetBrushFromTexture(Texture, false);
	}

	SetItemDesc(LastHoveredIndex);
}

void UInventoryUserWidget::SetItemDesc(const uint32 InIndex)
{
	if (InIndex == (uint32)-1) { return; }
	TWeakPtr<FItemData> ItemData;
	if (InIndex == (uint32)-2)
	{
		ItemData = InventorySubsystem->Weapon;
	}
	else
	{
		ItemData = InventorySubsystem->Inventory[InIndex];
	}
	SetItemDesc(ItemData);
}

void UInventoryUserWidget::SetItemDesc(TWeakPtr<FItemData> InData)
{
	if (InData.IsValid())
	{
		ItemDesc->SetText(InData.Pin()->ItemDesc);
	}
	else
	{
		ItemDesc->SetText(FText());
	}
}

void UInventoryUserWidget::OnItemBtnClicked(UInventoryItemUserWidget* InWidget)
{
	const uint32 Index = InWidget->ItemIndex;

	TWeakPtr<FItemData> ItemData = InventorySubsystem->Inventory[Index];
	if (ItemData.IsValid())
	{
		InventorySubsystem->UseItem(this, Index);
	}
}

void UInventoryUserWidget::OnWeaponBtnClicked(UInventoryItemUserWidget* InWidget)
{
	if (!InventorySubsystem->Weapon) { return; }

	InventorySubsystem->UnEquipWeapon(this);
}

void UInventoryUserWidget::OnWeaponBtnHovered(UInventoryItemUserWidget* InWidget)
{
	LastHoveredIndex = (uint32) - 2;
	SetItemDesc(LastHoveredIndex);
}
