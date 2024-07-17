#include "NetDriver.h"

bool UNetDriver::InitListen(FNetworkNotify InNotify, FURL& ListenURL, const bool bReuseAddressAndPort, const uint8 BacklogCount, TSubclassOf<UNetConnection> InNetConnectionClass)
{
	
	if (!InitBase(InNotify, ListenURL, InNetConnectionClass))
	{
		return false;
	}
	bServer = true;

	Acceptor = make_shared<boost::asio::ip::tcp::acceptor>(Context,
		tcp::endpoint(tcp::v4(), (boost::asio::ip::port_type)ListenURL.Port), bReuseAddressAndPort);

	for (uint8 i = 0; i < BacklogCount; i++)
	{
		StartAccept();
	}

	return true;
}

void UNetDriver::Send(UNetConnection* TargetConnection, FPacketHeader* Packet)
{
	TargetConnection->Send(Packet);
}

void UNetDriver::Send(UNetConnection* TargetConnection, const uint32 PacketID, void* PacketBody, const uint32 BodySize)
{
	TargetConnection->Send(PacketID, PacketBody, BodySize);
}

bool UNetDriver::InitBase(FNetworkNotify InNotify, FURL& InURL, TSubclassOf<UNetConnection> InNetConnectionClass)
{
	if (bInit)
	{
		E_Log(error, "이미 초기화 되어 있습니다.");
		return false;
	}

	bInit = true;
	NetConnectionClass = InNetConnectionClass;
	URL = InURL;
	NetworkNotify = InNotify;
	if (!NetConnectionClass)
	{
		E_Log(error, "NetConnectionClass Is nullptr");
		return false;
	}
	return true;
}

void UNetDriver::Tick(float DeltaSeconds)
{
	boost::system::error_code ErrorCode;
	// 이전프레임까지 쌓여있던 작업들을 실행한다.

	uint32 PollCountPerTick = 0;
	while(uint32 n = Context.poll_one(ErrorCode))
	{
		if (ErrorCode)
		{
			E_Log(error, "Context poll one : {} ", ErrorCode.message());

		}
		PollCountPerTick += n;
		//질문1) 왜 한개씩이 아니라 n개씩 증가하는가?
		if (PollCountPerTick >= 1000)
		{
			break;
		}
	}
}

void UNetDriver::OnConnected(UNetConnection* NetConnection)
{
	if (bServer)
	{
		MapOpenConnection.insert(make_pair(NetConnection, Cast<UNetConnection>(NetConnection)));
		MapPendingConnection.erase(NetConnection);
	}
	NetworkNotify.OnConnect(this, NetConnection);
}

void UNetDriver::OnConectionClosed(UNetConnection* NetConnection)
{
	if (NetConnection->GetConnectionState() != EConnectionState::USOCK_Pending)
	{
		NetworkNotify.OnConnectionClosed(this, NetConnection);
	}

	if (bServer)
	{
		StartAccept(Cast<UNetConnection>(NetConnection));

		if (NetConnection->GetConnectionState() == EConnectionState::USOCK_Pending)
		{
			MapPendingConnection.erase(NetConnection);
		}
		else if (NetConnection->GetConnectionState() == EConnectionState::USOCK_Open)
		{
			MapOpenConnection.erase(NetConnection);
		}
		else
		{
			E_Log(fatal, "check!");
		}
	}
}

void UNetDriver::OnReceived(UNetConnection* NetConnection, FPacketHeader* PacketHeader)
{
	if (PacketHeader->GetPacketID() == FPacketHeader::EPreDefinedPacketID::EHelloPacket)
	{
		NetConnection->OnConnect();

		if (bServer)
		{
			E_Log(trace, "Send to {} HelloPacket", to_string(NetConnection->GetName()));
			NetConnection->Send(FPacketHeader::EPreDefinedPacketID::EHelloPacket, nullptr, 0);
		}
	}
	else if (NetConnection->GetConnectionState() == EConnectionState::USOCK_Open)
	{
		NetworkNotify.OnRecv(this, NetConnection, PacketHeader);
	}
	else
	{	// USOCK_Open 상태가 아닌데, HelloPacket이 아니라면
		// 비정상적인 요청으로 간주하고 강제로 연결을 끊는다.
		NetConnection->Shutdown();
		return;
	}

	// 이 부분에서 USOCK_Closed가 됐다면 Kick된 상황
	const EConnectionState State = NetConnection->GetConnectionState();
	if (State != EConnectionState::USOCK_Closed)
	{
		NetConnection->ReadPacketHeader();
	}
}

UNetDriver::UNetDriver()
{

}

UNetDriver::~UNetDriver()
{
	
}

void UNetDriver::StartAccept(shared_ptr<UNetConnection> InReuseConnection)
{
	if (InReuseConnection)
	{
		InReuseConnection->CleanUp();
	}
	
	shared_ptr<UNetConnection> NewConnection = InReuseConnection ? InReuseConnection : NewObject<UNetConnection>(this,NetConnectionClass);
	if (!InReuseConnection)
	{
		NewConnection->InitRemoteConnection(bServer, URL, Context,
			bind(&ThisClass::OnClientAccepted, this, placeholders::_1),
			bind(&ThisClass::OnConnected, this, placeholders::_1),
			bind(&ThisClass::OnConectionClosed, this, placeholders::_1),
			bind(&ThisClass::OnReceived, this, placeholders::_1, placeholders::_2));
	}
	MapBacklog.insert(make_pair(NewConnection.get(), NewConnection));

	Acceptor->async_accept(*NewConnection->GetSocket(),
		[this,NewConnection,InReuseConnection](const boost::system::error_code& Error)
		{
			if (Error)
			{
				E_Log(error, "AsyncAccept error: {}", Error.message());

				StartAccept(NewConnection);
				return;
			}
			E_Log(trace, "New Client Accept: {}", to_string(NewConnection->GetName()));

			// Move NewConnection Backlog to PendingConnection.
			MapBacklog.erase(NewConnection.get());

			MapPendingConnection.insert(make_pair(NewConnection.get(), NewConnection));

			if (InReuseConnection == nullptr)
			{
				StartAccept();
			}

			NewConnection->OnPendingConnect();
		}
	);
}

//NetDriver 
void UNetDriver::OnClientAccepted(UNetConnection* NetConnection)
{

}

void UNetDriver::OnPendingConnected(UNetConnection* NetConnection)
{
}

bool UNetDriver::InitConnect(FNetworkNotify InNotify, FURL& ConnectURL, TSubclassOf<UNetConnection> InNetConnectionClass)
{
	if (!InitBase(InNotify, ConnectURL, InNetConnectionClass))
	{
		return false;
	}
	bServer = false;

	shared_ptr<UNetConnection> NewConnection = NewObject<UNetConnection>(this, NetConnectionClass);
	bool bResult = NewConnection->InitRemoteConnection(bServer, URL, Context,
		bind(&ThisClass::OnPendingConnected, this, placeholders::_1),
		bind(&ThisClass::OnConnected, this, placeholders::_1),
		bind(&ThisClass::OnConectionClosed, this, placeholders::_1),
		bind(&ThisClass::OnReceived, this, placeholders::_1, placeholders::_2));

	if (!bResult)
	{
		return false;
	}

	ClientConnection = NewConnection;

	return true;
}
