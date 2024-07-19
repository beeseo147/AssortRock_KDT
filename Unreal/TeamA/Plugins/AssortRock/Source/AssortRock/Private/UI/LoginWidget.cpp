// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoginWidget.h"
#include "Subsystem/ARServerSubsystem.h"
#include "UI/ChannelListWidget.h"

#ifdef LOGIN_TEST
#pragma data_seg(".share")
#pragma comment(linker, "/SECTION:.share,RWS")
static TAtomic<int32> gTestBotIndex = 0;

int32 CurrentBotIndex = 0;
const int32 MaxAccountCount = 20;
FString IDs[MaxAccountCount];
FString Passwords[MaxAccountCount];
#endif

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ARServerSubsystem = GetGameInstance()->GetSubsystem<UARServerSubsystem>();
	ARServerSubsystem->OnConnectionStateChange.AddDynamic(this, &ThisClass::OnConnectionStateChange);
	ARServerSubsystem->SetOnRecvedFunction(std::bind(&ThisClass::OnRecvedFromServer, this, std::placeholders::_1));
	OnConnectionStateChange(ARServerSubsystem->GetConnectionState());

	IDBox->OnTextChanged.AddDynamic(this, &ThisClass::OnIDBoxTextChanged);
	PasswordBox->OnTextChanged.AddDynamic(this, &ThisClass::OnPasswordBoxTextChanged);
	PasswordBox->OnTextCommitted.AddDynamic(this, &ThisClass::OnPasswordBoxTextCommitted);
	PasswordBox->SetIsPassword(true);

	SendBtn->OnClicked.AddDynamic(this, &ThisClass::OnSendBtnClicked);

#ifdef LOGIN_TEST
	CurrentBotIndex = gTestBotIndex.AddExchange(1);
	for (int32 i = 0; i < MaxAccountCount; ++i)
	{
		IDs[i] = TEXT("qwer") + FString::FromInt(i);
		Passwords[i] = TEXT("1234");
	}
	IDBox->SetText(FText::FromString(IDs[CurrentBotIndex]));
	PasswordBox->SetText(FText::FromString(Passwords[CurrentBotIndex]));
	CreateAccountCheckBox->SetCheckedState(ECheckBoxState::Checked);
#endif
}

void ULoginWidget::NativeDestruct()
{
	Super::NativeDestruct();
#ifdef LOGIN_TEST
	gTestBotIndex = 0;
#endif
}

void ULoginWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULoginWidget::OnConnectionStateChange(uint32 NewConnectionState)
{
	EConnectionState ConnectionState = (EConnectionState)NewConnectionState;
	if (LastConnectionState == ConnectionState) { return; }
	LastConnectionState = ConnectionState;
	UE_LOG(LogTemp, Warning, TEXT("ConnectionState: %d"), NewConnectionState);

	switch (LastConnectionState)
	{
	case USOCK_Invalid:
		ServerState->SetFillColorAndOpacity(FLinearColor::Black);
		break;
	case USOCK_Closed:
		ServerState->SetFillColorAndOpacity(FLinearColor::Red);
		break;
	case USOCK_Pending:
		ServerState->SetFillColorAndOpacity(FLinearColor(1.f, 0.5f, 0.f, 1.f));
		break;
	case USOCK_Open:
		ServerState->SetFillColorAndOpacity(FLinearColor::Green);

#ifdef LOGIN_TEST
		if (!bOnce)
		{
			bOnce = true;
			OnSendBtnClicked();
		}
#endif
		break;
	default:
		break;
	}
}

void ULoginWidget::OnIDBoxTextChanged(const FText& Text)
{
	FText ResultText = RemoveDisallowedString(Text.ToString());
	IDBox->SetText(ResultText);
}

void ULoginWidget::OnPasswordBoxTextChanged(const FText& Text)
{
	FText ResultText = RemoveDisallowedString(Text.ToString());
	PasswordBox->SetText(ResultText);
}

void ULoginWidget::OnPasswordBoxTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		OnSendBtnClicked();
	}
}

void ULoginWidget::OnSendBtnClicked()
{
	MessageBlock->SetText(FText{});

	if (LastConnectionState != EConnectionState::USOCK_Open)
	{
		FText Msg = NSLOCTEXT("Login", "ConnectionError", "Connection not opened.");
		MessageBlock->SetText(Msg);
		return;
	}

	const FText ID = IDBox->GetText();
	const FText Password = PasswordBox->GetText();
	if (ID.IsEmpty() || Password.IsEmpty())
	{
		FText MsgEmptyID = NSLOCTEXT("Login", "EmptyID", "ID is empty!\n");
		FText MsgEmptyPassword = NSLOCTEXT("Login", "EmptyPassword", "Password is empty!\n");
		FString Msg;
		if (ID.IsEmpty())
		{
			Msg += MsgEmptyID.ToString();
		}
		if (Password.IsEmpty())
		{
			Msg += MsgEmptyPassword.ToString();
		}
		MessageBlock->SetText(FText::FromString(Msg));
		return;
	}

	if (CreateAccountCheckBox->GetCheckedState() == ECheckBoxState::Checked)
	{
		// Send Create Account packet
		ARServerSubsystem->SendCreateAccount(ID.ToString(), Password.ToString());
	}
	else
	{
		// Send Login packet
		ARServerSubsystem->SendLogin(ID.ToString(), Password.ToString());
	}

}

void ULoginWidget::OnRecvedFromServer(FARPacketHeader* Packet)
{
	EARPacketType PacketType = (EARPacketType)Packet->GetPacketID();
	switch (PacketType)
	{
	case EARPacketType::ECreateAccount_Successed:
	{
		FText Msg = NSLOCTEXT("Login", "CreateAccount_Successed", "CreateAccount Successed!");
		MessageBlock->SetText(Msg);
		break;
	}
	case EARPacketType::ECreateAccount_DuplicateAccount:
	{
		FText Msg = NSLOCTEXT("Login", "CreateAccount_DuplicateAccount", "This ID already exists!");
		MessageBlock->SetText(Msg);
		break;
	}
	case EARPacketType::ELogin_Successed:
	{
		FText Msg = NSLOCTEXT("Login", "ELogin_Successed", "Login Successed!");
		//MessageBlock->SetText(Msg);

		ARServerSubsystem->ClearOnRecvedFunction();
		RemoveFromParent();

		LoadClass<UClass>(ANY_PACKAGE, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/Login/UI/UI_ChannelList.UI_ChannelList_C'"),
			nullptr, LOAD_None, nullptr);
		UClass* WidgetClass = FindObject<UClass>(ANY_PACKAGE, 
			TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/Login/UI/UI_ChannelList.UI_ChannelList_C'"));
		UChannelListWidget* ChannelListWidget = CreateWidget<UChannelListWidget>(GetWorld(), WidgetClass);
		ChannelListWidget->AddToViewport();
		break;
	}
	case EARPacketType::ELogin_Failed:
	{
		FText Msg = NSLOCTEXT("Login", "ELogin_Failed", "Login Failed!");
		MessageBlock->SetText(Msg);
		break;
	}
	default:
		ensure(false);
		break;
	}
}

FText ULoginWidget::RemoveDisallowedString(const FString& InString)
{
	if (InString.IsEmpty()) { return FText(); }

	FString String = InString;
	for (int32 i = 0; i < String.Len();)
	{
		TCHAR Char = String[i];
		if (!(

			(TEXT('A') <= Char && Char <= TEXT('Z')) ||
			(TEXT('a') <= Char && Char <= TEXT('z')) ||
			(TEXT('0') <= Char && Char <= TEXT('9'))

			))
		{
			String.RemoveAt(i);
		}
		else
		{
			++i;
		}
	}

	//String.RemoveSpacesInline();

	{
		const int32 Length = String.Len();
		if (Length > IDPasswordMaxLength)
		{
			String = FString(IDPasswordMaxLength, *String);
		}
	}

	return FText::FromString(String);
}
