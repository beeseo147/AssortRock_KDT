#include "NetDriver.h"

void UNetDriver::Tick(float DeltaSeconds)
{
}

UNetDriver::UNetDriver()
{

}

UNetDriver::~UNetDriver()
{
	
}
bool UNetDriver::InitListen(FNetworkNotify InNotify, FURL& ListenURL, const bool bReuseAddressAndPort, const uint8 BacklogCount, TSubclassOf<UNetConnection> InNetConnectionClass)
{
	NetConnectionClass = InNetConnectionClass;
	URL = ListenURL;
	NetworkNotify = InNotify;
	if (!NetConnectionClass)
	{
		E_Log(error, "NetConnectionClass Is nullptr")
	}
	Acceptor = make_shared<tcp::acceptor>(Context,
		tcp::endpoint(tcp::v4(), (boost::asio::ip::port_type)ListenURL.Port), bReuseAddressAndPort);

	for (uint8 i = 0; i < BacklogCount; i++)
	{
		StartAccept();
	}

	return true;
}

void UNetDriver::StartAccept(shared_ptr<UNetConnection> InReuseConnection)
{
	shared_ptr<UNetConnection> NewConnection = InReuseConnection ? InReuseConnection : NewObject<UNetConnection>(this,NetConnectionClass);
	if (!InReuseConnection)
	{
		NewConnection->InitRemoteConnection(Context,
			bind(&ThisClass::OnClientConnectionClosed,this,std::placeholders::_1),
			bind(&ThisClass::OnClientReceived,this,placeholders::_1, placeholders::_2)
		);
		MapBacklog.insert(make_pair(NewConnection.get(), NewConnection));
	}
	Acceptor->async_accept(*NewConnection->GetSocket(),
		[](const boost::system::error_code& Error)
		{
			 // -----
			;
		}
}

void UNetDriver::OnClientConnectionClosed(UNetConnection* NetConnection)
{
}

void UNetDriver::OnClientReceived(UNetConnection* NetConnection, FPacketHeader* PacketHeader)
{
}
