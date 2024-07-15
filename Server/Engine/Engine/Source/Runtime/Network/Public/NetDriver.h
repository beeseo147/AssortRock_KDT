#pragma once
// AssortRock Inc.

#include "NetworkTypes.h"
#include "NetConnection.h"
#include "NetDriver.generated.h"

class UNetDriver;
struct FNetworkNotify
{
	friend class UNetDriver;
private:
	function<void(UNetDriver*, UNetConnection*)> OnConnect;
	function<void(UNetDriver*, UNetConnection*)> OnConnectionClosed;
	function<void(UNetDriver*, UNetConnection*, FPacketHeader*)> OnRecv;
};

UCLASS()
class NETWORK_API UNetDriver : public UObject
{
	GENERATED_BODY();
//-------------- Server 
public:
	/**
	 * Initialize the network driver in server mode (listener)
	 */
	virtual bool InitListen(FNetworkNotify InNotify,FURL& ListenURL,const bool bReuseAddressAndPort,
		const uint8 BacklogCount,TSubclassOf<UNetConnection> InNetConnectionClass = UNetConnection::StaticClass());

protected:
	void StartAccept(shared_ptr<UNetConnection> InReuseConnection = nullptr);

	void OnClientConnectionClosed(UNetConnection* NetConnection);
	void OnClientReceived(UNetConnection* NetConnection,FPacketHeader* PacketHeader);

protected:
	unordered_map<UNetConnection*, shared_ptr<UNetConnection>> MapBacklog;

//-------------- Clinet 
public:
	virtual void InitConnect(FNetworkNotify InNotify, FURL& ListenURL) {}

//-------------- 공통 
public:
	virtual void Tick(float DeltaSeconds);
public:
	UNetDriver();
	~UNetDriver();

protected:
	//
	TSubclassOf<UNetConnection> NetConnectionClass;
	FURL URL;
	FNetworkNotify NetworkNotify;
	//SERVER
	boost::asio::io_context Context;
	shared_ptr<boost::asio::ip::tcp::acceptor> Acceptor;
	
};  