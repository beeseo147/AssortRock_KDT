// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryItemUserWidget.h"

void UInventoryItemUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemBtn->OnHovered.AddDynamic(this, &ThisClass::OnItemBtnHovered);
	ItemBtn->OnClicked.AddDynamic(this, &ThisClass::OnItemBtnClicked);
}

void UInventoryItemUserWidget::OnItemBtnHovered()
{
	if (ItemBtnHovered.IsBound())
	{
		ItemBtnHovered.Execute(this);
	}
}

void UInventoryItemUserWidget::OnItemBtnClicked()
{
	if (ItemBtnClicked.IsBound())
	{
		ItemBtnClicked.Execute(this);
	}
}
