// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"
#include "LoginWidget.generated.h"

//#define LOGIN_TEST

UCLASS()
class ASSORTROCK_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UFUNCTION()
	void OnConnectionStateChange(uint32 NewConnectionState);
	UFUNCTION()
	void OnIDBoxTextChanged(const FText& Text);
	UFUNCTION()
	void OnPasswordBoxTextChanged(const FText& Text);
	UFUNCTION()
	void OnPasswordBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void OnSendBtnClicked();

protected:
	void OnRecvedFromServer(FARPacketHeader* Packet);

protected:
	FText RemoveDisallowedString(const FString& InString);

protected:
	// Green: Open
	// Orange: Pending
	// Red: Closed
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ServerState;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableTextBox* IDBox;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableTextBox* PasswordBox;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* SendBtn;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MessageBlock;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCheckBox* CreateAccountCheckBox;

	const int32 IDPasswordMaxLength = 15;

	EConnectionState LastConnectionState = (EConnectionState)-1;
	
#ifdef LOGIN_TEST
	bool bOnce = false;
#endif
protected:
	class UARServerSubsystem* ARServerSubsystem = nullptr;
};
