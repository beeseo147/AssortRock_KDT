// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChannelBtnWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ARServerSubsystem.h"

void UChannelBtnWidget::SetChannelInfo(const FString InIP, const uint16 InPort)
{
	IP = InIP;
	Port = InPort;
	ChannelButton->OnClicked.AddDynamic(this, &ThisClass::OnChannelButtonClicked);
}

void UChannelBtnWidget::SetUserCount(const int32 UserCount)
{
	CurrentUserCount->SetText(FText::FromString(FString::FromInt(UserCount)));
}

void UChannelBtnWidget::OnChannelButtonClicked()
{
	UARServerSubsystem* ARServerSubsystem = GetGameInstance()->GetSubsystem<UARServerSubsystem>();

	const FString URL = IP + TEXT(":") + FString::FromInt(Port); 
	const FString ID = ARServerSubsystem->GetLoginID();
	const FString Password = ARServerSubsystem->GetLoginPassword();
	const FString Options = TEXT("ID=") + ID + TEXT("?PW=") + Password;
	UGameplayStatics::OpenLevel(this, FName(URL), true, Options);
}
