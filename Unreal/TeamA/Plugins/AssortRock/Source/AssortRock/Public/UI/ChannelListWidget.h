// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "ChannelListWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSORTROCK_API UChannelListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnLogoutButtonClicked();

protected:
	virtual void NativeConstruct() override;

	void OnRecvedFromServer(FARPacketHeader* Packet);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UVerticalBox* ChannelVerticalBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* LogoutButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* LoginID;

protected:
	TArray<UChannelBtnWidget*> Channels;
	UClass* UI_ChannelBtnClass = nullptr;
	class UARServerSubsystem* ARServerSubsystem = nullptr;
};
