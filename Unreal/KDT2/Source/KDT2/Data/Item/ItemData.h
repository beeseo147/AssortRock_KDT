// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

class UItem;

USTRUCT()
struct KDT2_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

	FItemData() {}
	/*FItemData(const FItemData& InOther)
	{

	}*/

public:
	UPROPERTY()
	FName ItemName;

	UPROPERTY()
	uint32 CurrentBundleCount = 0;

public:
	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere)
	FText ItemDesc;

	UPROPERTY(EditAnywhere)
	uint32 MaxBundleCount = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItem> ItemFunctionClass;
};
