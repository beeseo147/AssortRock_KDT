// Fill out your copyright notice in the Description page of Project Settings.


#include "NetWork/ARNetConnection.h"
#include "Sockets.h"
void UARNetConnection::InitBase(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket, int32 InPacketOverhead)
{
	DisableAddressResolution();
	Super::InitBase(InDriver, InSocket, InURL, InState, InMaxPacket, InPacketOverhead);

}

void UARNetConnection::InitLocalConnection(UNetDriver* InDriver, FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket, int32 InPacketOverhead)
{
	Super::InitLocalConnection(InDriver, InSocket, InURL, InState, InMaxPacket, InPacketOverhead);
	Socket->SetNonBlocking(false);
	Socket->SetNoDelay(true);
	if (Socket->Connect(*RemoteAddr))
	{
		Socket->SetNonBlocking(true);
		SetConnectionState(EConnectionState::USOCK_Pending);
	}
	
}
