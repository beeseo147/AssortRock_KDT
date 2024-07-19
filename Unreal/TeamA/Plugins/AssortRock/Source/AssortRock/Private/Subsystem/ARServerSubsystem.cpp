// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/ARServerSubsystem.h"

void UARServerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ARNetDriver = NewObject<UARNetDriver>(this);

	ARNetDriver->SetWorld(GetWorld());
	FURL URL;
	URL.Host = TEXT("127.0.0.1");
	URL.Port = 9999;
	FString Error;
	if (ARNetDriver->InitConnect(this, URL, Error))
	{
		ARNetDriver->CleanUp();
		//서버에 접속실패.. 생략
	}

}

// 접속해제
void UARServerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	if (!ARNetDriver) { return; }

	ARNetDriver->CleanUp();

}

void UARServerSubsystem::NotifyConnect(UARNetConnection* Connection)
{
}

void UARServerSubsystem::NotifyConnectionClosed(UARNetConnection* Connection)
{
}

void UARServerSubsystem::NotifyReceivedRawPacket(UARNetConnection* Connection, FARPacketHeader* Packet)
{
}
