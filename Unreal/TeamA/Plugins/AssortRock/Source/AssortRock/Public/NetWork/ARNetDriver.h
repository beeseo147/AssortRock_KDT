// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IpNetDriver.h"
#include "ARNetConnection.h"
#include "ARNetDriver.generated.h"

class FARNetworkNotify : public FNetworkNotify
{
public:
	virtual void NotifyConnect(UARNetConnection* Connection) PURE_VIRTUAL(FARNetworkNotify::NotifyConnect, );
	virtual void NotifyConnectionClosed(UARNetConnection* Connection) PURE_VIRTUAL(FARNetworkNotify::NotifyConnectionClosed, );
	virtual void NotifyReceivedRawPacket(UARNetConnection* Connection, FARPacketHeader* Packet) PURE_VIRTUAL(FARNetworkNotify::NotifyReceivedRawPacket, );

private:
	virtual EAcceptConnection::Type NotifyAcceptingConnection() { check(false); return EAcceptConnection::Ignore; }
	virtual bool NotifyAcceptingChannel(class UChannel*) { check(false); return false; }
	virtual void NotifyControlMessage(UNetConnection*, uint8, class FInBunch&) { check(false); }
};
UCLASS()
class ASSORTROCK_API UARNetDriver : public UIpNetDriver
{
	GENERATED_BODY()
	
public:
	virtual bool InitConnectionClass(void) override;
	virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;
	virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;

	virtual void TickDispatch(float DeltaTime) override;
	virtual void LowLevelSend(TSharedPtr<const FInternetAddr> Address, void* Data, int32 CountBits, FOutPacketTraits& Traits) override;
	//virtual void SendPacket(FARPacketHeader* Packet, int32 CountBits);

	virtual void CleanUp();
protected:
	/**
	 * Creates, initializes and binds a socket using the given bind address information.
	 *
	 * @param BindAddr				the address to bind the new socket to, will also create the socket using the address protocol using CreateSocketForProtocol
	 * @param Port					the port number to use with the given bind address.
	 * @param bReuseAddressAndPort	if true, will set the socket to be bound even if the address is in use
	 * @param DesiredRecvSize		the max size of the recv buffer for the socket
	 * @param DesiredSendSize		the max size of the sending buffer for the socket
	 * @param Error					a string reference that will be populated with any error messages should an error occur
	 *
	 * @return if the socket could be created and bound with all the appropriate options, a pointer to the new socket is given, otherwise null
	 */
	FUniqueSocket CreateAndBindSocket(TSharedRef<FInternetAddr> BindAddr, int32 Port, bool bReuseAddressAndPort, int32 DesiredRecvSize, int32 DesiredSendSize, FString& Error) override;
	/**
	 * Creates a socket set up for communication using the given protocol. This allows for explicit creation instead of inferring type for you.
	 *
	 * @param ProtocolType	an FName that represents the protocol to allocate the new socket under. Typically set to None or a value in FNetworkProtocolTypes
	 * @return				an FSocket if creation succeeded, nullptr if creation failed.
	 */
	virtual FUniqueSocket CreateSocketForProtocol(const FName& ProtocolType) override;
protected:
	bool ReadPacket();
	bool ReadPacketSome(uint8* const InTarget, const uint32 InReadSize);

protected:

	FARNetworkNotify* ARNetworkNotify = nullptr;
	UARNetConnection* ARNetConnection = nullptr;
	FURL URL;
};
