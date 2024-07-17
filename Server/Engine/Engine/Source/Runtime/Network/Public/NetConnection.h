#pragma once
// AssortRock Inc.

#include "NetworkTypes.h"
#include "NetConnection.generated.h"

#pragma pack(push,1)
struct FPacketHeader
{
	enum EPreDefinedPacketID : uint32
	{
		EHelloPacket = 2,	// Client to Server; 클라가 처음 접속하며 서버로 보내는 Packet
		// Server to Client; 클라로 부터 EHelloPacket를 수신하면 응답으로 보낸다
		EEnd
	};

public:
	FPacketHeader() = default;
	FPacketHeader(const uint32 NewPacketID) : PacketID(NewPacketID) {}
	FPacketHeader(const uint32 NewPacketID, const uint32 NewPayloadSize) :
		PacketID(NewPacketID), Payload(NewPayloadSize) {}
	void SetPayload(const uint32 InPayload) { Payload = InPayload; }
	void SetPacketID(const uint32 InPacketID) { PacketID = InPacketID; }
	uint32 GetPayload() const { return Payload; }
	uint32 GetPacketID() const { return PacketID; }

private:
	// Packet의 본문의 크기
	uint32 Payload = 0;
	uint32 PacketID = 0;
};

#pragma pack(pop)

enum EConnectionState : uint8
{
	USOCK_Invalid = 0, // Connection is invalid, possibly uninitialized.
	USOCK_Closed = 1, // Connection permanently closed.
	USOCK_Pending = 2, // Accept는 했으나, 아직 아무런 Packet도 받지 못한
	USOCK_Open = 3, // Connection is open.
};

UCLASS()
class NETWORK_API UNetConnection : public UObject
{
	GENERATED_BODY();
	friend class UNetDriver;


protected:
	void Send(FPacketHeader* Packet);
	void Send(const uint32 PacketID, void* PacketBody, const uint32 BodySize);
	void LowLevelSend(void* Data, const uint64 Size);
public:
	bool InitRemoteConnection(
		const bool bServer,
		const FURL& InURL,
		boost::asio::io_context& InContext,
		function<void(UNetConnection*)> InPendingConnectFunction, // Server의 경우 Accept 시점, Client의 경우 Connect 시점
		function<void(UNetConnection*)> InConnectFunction, // Hello Packet을 받은 시점
		function<void(UNetConnection*)> InConnectionClosedFunction,
		function<void(UNetConnection*, FPacketHeader*)> InRecvFunction);

	FSocket* GetSocket()const { return Socket.get(); }

	void OnAccept();
	void OnConnect();
	// 재사용 직전에 CleanUp
	void CleanUp();
protected:
	// 재사용 직전에 Shutdown
	virtual void Shutdown();
	void OnPendingConnect();
	void OnConnect();
	void InitBase(const FURL& InURL, boost::asio::io_context& InContext);

	EConnectionState GetConnectionState() const { return ConnectionState; }
	void SetConnectionState(const EConnectionState State);

	void ReadPacketHeader();
	void ReadPacketBody(const FPacketHeader& InPacketHeader);
public:
	UNetConnection();
   	~UNetConnection();
private:
	FPacketHeader RecvPacketHeaderBuffer;
	boost::pool<> BufferPool{ 1460 * 2 }; // TCP MTU Payload size * 2
private:
	FPacketHeader RecvPacketHeaderBuffer;
private:
	bool bNetDriverIsServer = false;
	FURL URL;
	uint64 UniqueID = 0;

	uint16 RemotePort = 0;
	string RemoteAddress;

	chrono::system_clock::time_point PendingConnectTime;

	EConnectionState ConnectionState = EConnectionState::USOCK_Closed;
	unique_ptr<FSocket> Socket;
	function<void(UNetConnection*)> PendingConnectFunction;
	function<void(UNetConnection*)> ConnectFunction;
	function<void(UNetConnection*)> ConnectionClosedFunction;
	function<void(UNetConnection*, FPacketHeader*)> RecvFunction;
};