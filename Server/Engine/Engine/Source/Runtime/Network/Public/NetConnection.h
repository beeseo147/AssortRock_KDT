#pragma once
// AssortRock Inc.

#include "NetworkTypes.h"
#include "NetConnection.generated.h"

#pragma pack(push,1)
struct FPacketHeader
{
private:

	//Packet의 본문의 크기
	uint32 Payload = 0;
	uint32 PacketID = 0;

};

#pragma pack(pop)

enum EConnectionState : uint8
{
 	USOCK_Closed = 1, // Connection permanently closed.
	USOCK_Pending = 2, // Accept는 했으나, 아직 아무런 Packet도 받지 못한
	USOCK_Open = 3, // Connection is open.
};

UCLASS()
class NETWORK_API UNetConnection : public UObject
{
	GENERATED_BODY();

public:
	void InitRemoteConnection(boost::asio::io_context& InContext,
		function<void(UNetConnection*)> InOnConnectionClose,
		function<void(UNetConnection*, FPacketHeader*)> InOnRecv
	);

	FSocket* GetSocket()const { return Socket.get(); }
protected:
	void InitBase(boost::asio::io_context& InContext);
public:
	UNetConnection();
	~UNetConnection();

private:
	EConnectionState ConnectionState = EConnectionState::USOCK_Closed;
	unique_ptr<FSocket> Socket;
	function<void(UNetConnection*)> OnConnectionClose;
	function<void(UNetConnection*,FPacketHeader*)> OnRecv;
};