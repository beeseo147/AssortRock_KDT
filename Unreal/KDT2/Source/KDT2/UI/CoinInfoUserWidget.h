// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CoinInfoUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API UCoinInfoUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	FText OnCoinTextChange();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* RemainCoinText;

};
