// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/ARNetDriver.h"

bool UARNetDriver::InitConnectionClass(void)
{
	return false;
}

bool UARNetDriver::InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error)
{
	Super::InitBase(bInitAsClient, InNotify, URL, bReuseAddressAndPort,Error);
	return false;
}

bool UARNetDriver::InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error)
{
	Super::InitConnect(InNotify, ConnectURL, Error);
	if (!InitBase(true, InNotify, ConnectURL, false, Error))
	{
		UE_LOG(LogNet, Warning, TEXT("Failed to init NetDriver ConnectURL : %s , %d %s"), *ConnectURL.Host, ConnectURL.Port,*Error);
	}
	FSocket* Socket = GetSocket();

	ServerConnection = NewObject<UNetConnection>(this, NetConnectionClass);
	ServerConnection->InitLocalConnection(this, Socket, ConnectURL, EConnectionState::USOCK_Pending);

	if (ServerConnection->GetConnectionState() != EConnectionState::USOCK_Pending)
	{
		CleanUp();
		return false;
	}
	ARNetConnection = Cast<UARNetConnection>(ServerConnection);
	check(ARNetConnection);

	ARNetworkNotify = (FARNetworkNotify*)InNotify;
	InNotify->NotifyAcceptedConnection(Cast<UARNetConnection>(ARNetConnection));

	return true;
}

void UARNetDriver::TickDispatch(float DeltaTime)
{
	Super::TickDispatch(DeltaTime);
}

void UARNetDriver::LowLevelSend(TSharedPtr<const FInternetAddr> Address, void* Data, int32 CountBits, FOutPacketTraits& Traits)
{
}

void UARNetDriver::CleanUp()
{
}

FUniqueSocket UARNetDriver::CreateAndBindSocket(TSharedRef<FInternetAddr> BindAddr, int32 Port, bool bReuseAddressAndPort, int32 DesiredRecvSize, int32 DesiredSendSize, FString& Error)
{
	return FUniqueSocket();
}

FUniqueSocket UARNetDriver::CreateSocketForProtocol(const FName& ProtocolType)
{
	return FUniqueSocket();
}

bool UARNetDriver::ReadPacket()
{
	return false;
}

bool UARNetDriver::ReadPacketSome(uint8* const InTarget, const uint32 InReadSize)
{
	return false;
}
