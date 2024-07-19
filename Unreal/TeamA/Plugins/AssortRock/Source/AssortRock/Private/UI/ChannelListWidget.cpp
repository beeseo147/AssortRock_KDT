// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChannelListWidget.h"
#include "UI/ChannelBtnWidget.h"
#include "Subsystem/ARServerSubsystem.h"

void UChannelListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ARServerSubsystem = GetGameInstance()->GetSubsystem<UARServerSubsystem>();
	ARServerSubsystem->SetOnRecvedFunction(std::bind(&ThisClass::OnRecvedFromServer, this, std::placeholders::_1));
	
	{
		FString String = TEXT("ID: ") + ARServerSubsystem->GetLoginID();
		LoginID->SetText(FText::FromString(String));
	}

	LogoutButton->OnClicked.AddDynamic(this, &ThisClass::OnLogoutButtonClicked);

	LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/Login/UI/UI_ChannelBtn.UI_ChannelBtn_C'"),
		nullptr, LOAD_None, nullptr);
	UI_ChannelBtnClass = FindObject<UClass>(ANY_PACKAGE,
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/Login/UI/UI_ChannelBtn.UI_ChannelBtn_C'"));
	ChannelVerticalBox->ClearChildren();

	ARServerSubsystem->SendRequestServerInfo();
}

void UChannelListWidget::OnLogoutButtonClicked()
{
	// Send Logout 
	ARServerSubsystem->SendLogout();
	ARServerSubsystem->ClearOnRecvedFunction();
	RemoveFromParent();

	UClass* WidgetClass = FindObject<UClass>(ANY_PACKAGE,
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/Login/UI/UI_Login.UI_Login_C'"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	Widget->AddToViewport();
}

void UChannelListWidget::OnRecvedFromServer(FARPacketHeader* Packet)
{
	EARPacketType PacketType = (EARPacketType)Packet->GetPacketID();
	switch (PacketType)
	{
	case EARPacketType::ERequestServerInfo_Ack:
	{
#pragma pack(push, 1)
		struct FRequestServerInfoAck : public FARPacketHeader
		{
			uint16 ChannelCount;
			struct FInfo
			{
				uint16 CurrentPlayers;
				uint16 MaxPlayers;

				char IP[15];
				uint16 Port;
			};
			FInfo ChannelInfo[30];
		};

		FRequestServerInfoAck* RequestServerInfoAck = (FRequestServerInfoAck*)Packet;

		ChannelVerticalBox->ClearChildren();
		Channels.Empty();
		Channels.Reserve(RequestServerInfoAck->ChannelCount);
		for (uint16 i = 0; i < RequestServerInfoAck->ChannelCount; ++i)
		{
			FRequestServerInfoAck::FInfo& Info = RequestServerInfoAck->ChannelInfo[i];

			UChannelBtnWidget* Widget = CreateWidget<UChannelBtnWidget>(GetWorld(), UI_ChannelBtnClass);

			FString IP = ANSI_TO_TCHAR(Info.IP);
			FString ChannelString = TEXT("C") + FString::FromInt(i + 1) + " " + IP + ":" + FString::FromInt(Info.Port);
			Widget->ChannelInfo->SetText(FText::FromString(ChannelString));
			Widget->CurrentUserCount->SetText(FText::FromString(FString::FromInt(Info.CurrentPlayers)));
			Widget->MaxUserCount->SetText(FText::FromString(FString::FromInt(Info.MaxPlayers)));
			ChannelVerticalBox->AddChildToVerticalBox(Widget);

			Widget->SetChannelInfo(IP, Info.Port);
			Channels.Add(Widget);
		}

#pragma pack(pop)
		break;
	}
	case EARPacketType::EServerCurrentPlayerUpdate:
	{
#pragma pack(push, 1)
		struct FServerCurrentPlayerUpdatePacket : public FARPacketHeader
		{
			char IP[15] = {};
			uint16 ServerPort = 0;
			uint16 CurrentPlayers = 0;
		};
#pragma pack(pop)
		FServerCurrentPlayerUpdatePacket* NewPacket = (FServerCurrentPlayerUpdatePacket*)Packet;
		const FString ChannelIP = ANSI_TO_TCHAR(NewPacket->IP);
		const uint16 ChannelPort = NewPacket->ServerPort;
		const uint16 CurrentPlayers = NewPacket->CurrentPlayers;

		for (UChannelBtnWidget* It : Channels)
		{
			const FString CurrentChannelIP = It->GetChannelIP();
			const uint16 CurrentChannelPort = It->GetChannelPort();
			if (CurrentChannelIP == ChannelIP && CurrentChannelPort == ChannelPort)
			{
				It->SetUserCount(CurrentPlayers);
				break;
			}
		}

		break;
	}
	}
}
