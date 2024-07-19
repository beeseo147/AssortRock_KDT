#include "NetDriver.h"

//서버 모드에서 네트워크 연결을 초기화합니다.
// 지정된 포트에서 연결을 대기하고, 연결이 들어오면 StartAccept 함수를 호출하여 
// 새로운 연결을 처리합니다.
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
void UNetDriver::StartAccept(shared_ptr<UNetConnection> InReuseConnection)
{
	if (InReuseConnection)
	{
		InReuseConnection->CleanUp();
	}

	shared_ptr<UNetConnection> NewConnection = InReuseConnection ? InReuseConnection : NewObject<UNetConnection>(this, NetConnectionClass);
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
		[this, NewConnection, InReuseConnection](const boost::system::error_code& Error)
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

//클라이언트 모드에서 네트워크 연결을 초기화합니다.
// 지정된 주소와 포트로 연결을 시도하고, 
// 연결이 성공하면 ClientConnection 멤버에 저장합니다.

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

//-------------- 공통 
//이 함수는 이미 생성된 FPacketHeader 객체를 사용하여 패킷을 전송합니다.
//FPacketHeader 객체에는 패킷의 헤더 정보(예: 패킷 ID, 크기 등)가 포함되어 있습니다.
//이 함수를 사용하면 패킷 헤더 정보를 직접 생성할 필요가 없습니다.
void UNetDriver::Send(UNetConnection* TargetConnection, FPacketHeader* Packet)
{
	TargetConnection->Send(Packet);
}

//이 함수는 패킷 ID, 패킷 본문 데이터, 그리고 본문 크기를 직접 전달합니다.
//이 함수를 사용하면 FPacketHeader 객체를 직접 생성할 필요가 있습니다.
//이 함수는 패킷 헤더 정보를 직접 생성해야 하는 경우에 유용합니다.
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

struct FPendingConnectionTimeOutTask : public FTask
{
	FPendingConnectionTimeOutTask(UNetDriver* InNetDriver)
		: NetDriver(InNetDriver) {}

	virtual void ExecuteTask() override
	{
		auto Now = chrono::system_clock::now();

		vector<UNetConnection*> TimeoutConnections;

		for (auto& It : NetDriver->MapPendingConnection)
		{
			auto& PedingConnectTime = It.second->GetPendingConnectTime();
			auto Difftime = std::chrono::duration_cast<std::chrono::seconds>(Now - PedingConnectTime);
			//30초이상 입력이없으면
			if (Difftime.count() >= 30)
			{
				TimeoutConnections.push_back(It.first);

			}
		}

		for (auto It : TimeoutConnections)
		{
			E_Log(trace, "{}", to_string(It->GetName()));
			It->CleanUp();
		}
	}

private:
	UNetDriver* NetDriver = nullptr;
};
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

	InvokeTask<FPendingConnectionTimeOutTask>(this);

}
//NetDriver
// 새로운 클라이언트 연결이 들어오면 호출됩니다.
//  이 클라이언트를 MapPendingConnection에 추가합니다. 
void UNetDriver::OnClientAccepted(UNetConnection* NetConnection)
{
	MapPendingConnection.insert(make_pair(NetConnection, Cast<UNetConnection>(NetConnection)));
}
// 보류 중인 연결이 성공하면 호출됩니다.
//  이 때 클라이언트에게 HelloPacket을 전송합니다.
void UNetDriver::OnPendingConnected(UNetConnection* NetConnection)
{
	NetConnection->Send(FPacketHeader::EHelloPacket, nullptr, 0);
}
// 연결이 성공하면 호출됩니다. 
// 서버 모드에서는 MapOpenConnection에 추가하고 MapPendingConnection에서 제거합니다.
// 그리고 NetworkNotify의 OnConnect 함수를 호출합니다.
void UNetDriver::OnConnected(UNetConnection* NetConnection)
{
	if (bServer)
	{
		MapOpenConnection.insert(make_pair(NetConnection, Cast<UNetConnection>(NetConnection)));
		MapPendingConnection.erase(NetConnection);
	}
	NetworkNotify.OnConnect(this, NetConnection);
}
//연결이 종료되면 호출됩니다.
// 서버 모드에서는 MapOpenConnection 또는 MapPendingConnection에서 제거하고, 
// StartAccept를 호출하여 새로운 연결을 받습니다.
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
//패킷이 수신되면 호출됩니다.
// HelloPacket인 경우 처리하고, 그 외의 경우 NetworkNotify의 OnRecv 함수를 호출합니다. 
// 비정상적인 패킷인 경우 연결을 종료합니다.
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