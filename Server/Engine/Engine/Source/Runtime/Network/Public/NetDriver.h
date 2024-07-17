#pragma once
// AssortRock Inc.

#include "NetworkTypes.h"
#include "NetConnection.h"
#include "NetDriver.generated.h"

class UNetDriver;
struct FNetworkNotify
{
	friend class UNetDriver;
public:
	FNetworkNotify(
		function<void(UNetDriver*, UNetConnection*)> InOnConnect,
		function<void(UNetDriver*, UNetConnection*)> InOnConnectionClosed,
		function<void(UNetDriver*, UNetConnection*, FPacketHeader*)> InOnRecv) :
		OnConnect(InOnConnect), OnConnectionClosed(InOnConnectionClosed), OnRecv(InOnRecv) {}

private:
	FNetworkNotify() {}

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

protected:
	// 아직 async_accept 상태인 Connection
	unordered_map<UNetConnection*, shared_ptr<UNetConnection>> MapBacklog;
	// 클라로 부터 connect 되었으나, Hello Packet을 받지 못한 Connection
	unordered_map<UNetConnection*, shared_ptr<UNetConnection>> MapPendingConnection;
	// 클라로 부터 Hello Packet을 받은 Connection
	unordered_map<UNetConnection*, shared_ptr<UNetConnection>> MapOpenConnection;
	
//-------------- Clinet 
public:
	virtual bool InitConnect(FNetworkNotify InNotify, FURL& ConnectURL, TSubclassOf<UNetConnection> InNetConnectionClass = UNetConnection::StaticClass());
	engine_weak_ptr<UNetConnection> GetClientConnection() { return ClientConnection; }

protected:
	shared_ptr<UNetConnection> ClientConnection;
	
//-------------- 공통 
public:
	void Send(UNetConnection* TargetConnection, FPacketHeader* Packet);
	void Send(UNetConnection* TargetConnection, const uint32 PacketID, void* PacketBody, const uint32 BodySize);
	virtual bool InitBase(FNetworkNotify InNotify, FURL& InURL, TSubclassOf<UNetConnection> InNetConnectionClass);

	virtual void Tick(float DeltaSeconds);

	//Server
	virtual void OnClientAccepted(UNetConnection* NetConnection);

	// Client: connect 성공 시
	virtual void OnPendingConnected(UNetConnection* NetConnection);

	// Client: connect이후, HelloPacket을 수신
	// Server: accept이후, HelloPacket을 수신
	virtual void OnConnected(UNetConnection* NetConnection);

	// Common
	virtual void OnConectionClosed(UNetConnection* NetConnection);
	virtual void OnReceived(UNetConnection* NetConnection, FPacketHeader* PacketHeader);

public:
	UNetDriver();
	~UNetDriver();

protected:
	bool bInit = false;
	bool bServer = false;
	TSubclassOf<UNetConnection> NetConnectionClass;
	FURL URL;
	FNetworkNotify NetworkNotify;
	//SERVER
	boost::asio::io_context Context;
	shared_ptr<boost::asio::ip::tcp::acceptor> Acceptor;
	
};  