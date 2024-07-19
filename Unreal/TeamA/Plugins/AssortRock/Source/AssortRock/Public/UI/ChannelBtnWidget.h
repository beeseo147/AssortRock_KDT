// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ChannelBtnWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSORTROCK_API UChannelBtnWidget : public UUserWidget
{
	GENERATED_BODY()
	friend class UChannelListWidget;
public:
	void SetChannelInfo(const FString InIP, const uint16 InPort);
	void SetUserCount(const int32 UserCount);
	
	FString GetChannelIP() const { return IP; }
	uint16 GetChannelPort() const { return Port; }

protected:
	UFUNCTION()
	void OnChannelButtonClicked();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ChannelButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ChannelInfo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* MaxUserCount;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CurrentUserCount;

protected:
	FString IP;
	uint16 Port;
};
