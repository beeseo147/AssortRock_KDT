// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "InventoryItemUserWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnInvenButtonEvent, UInventoryItemUserWidget* /*Widget*/);

UCLASS()
class KDT2_API UInventoryItemUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnItemBtnHovered();
	UFUNCTION()
	void OnItemBtnClicked();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ItemBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemImage;

	uint32 ItemIndex = (uint32)-1;

	FOnInvenButtonEvent ItemBtnHovered;
	FOnInvenButtonEvent ItemBtnClicked;
};
