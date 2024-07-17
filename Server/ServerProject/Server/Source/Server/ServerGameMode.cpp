#include "ServerGameMode.h"

void AServerGameMode::BeginPlay()
{
	Super::BeginPlay();

	NetDriver = NewObject<UNetDriver>(this);

	FNetworkNotify NetworkNotify = FNetworkNotify
	(
		[this](UNetDriver*, UNetConnection*) {},
		[this](UNetDriver*, UNetConnection*) {},
		[this](UNetDriver*, UNetConnection*, FPacketHeader*) {}
	);

	FURL URL;
	NetDriver->InitListen(NetworkNotify, URL, true, 5);

	auto& Vector = ObjectMap[UNetDriver::StaticClass()];
	for (engine_weak_ptr<UObject> It : Vector)
	{
		engine_weak_ptr<UNetDriver> ItNet = Cast<UNetDriver>(It);
	}
}

void AServerGameMode::OnRecv(UNetDriver* InNetDriver, UNetConnection* InNetConnection, FPacketHeader* InPacketHeader)
{

	//EARPacketType PacketType = (EARPacketType)InPacketHeader->GetPacketID();
	//switch (PacketType)
	//{
	//case EARPacketType::EMessage:
	//{
	//	FMessagePacket* MessagePacket = (FMessagePacket*)InPacketHeader;
	//	string Message = string(MessagePacket->Buffer.begin(), MessagePacket->Buffer.end());
	//	E_LOG(trace, "{}", Message);

	//	MessagePacket->Buffer[12] = '2';

	//	NetDriver->Send(InNetConnection, InPacketHeader);
	//	break;
	//}
	//case EARPacketType::ELogin:
	//{
	//	struct FCreateAccountPacket : public FAccountPacket
	//	{
	//		FCreateAccountPacket() {}
	//	};
	//	FCreateAccountPacket* Packet = (FCreateAccountPacket*)InPacketHeader;

	//	E_LOG(trace, "ID: {}, Password: {}", Packet->ID.data(), Packet->Password.data());
	//	if (Packet->ID.empty() || Packet->Password.empty())
	//	{
	//		E_LOG(error, "ID or Password is empty");
	//		InNetDriver->KickNetConnection(InNetConnection);
	//		break;
	//	}

	//	// 회원가입 처리

	//	break;
	//}
	//default:
	//	E_LOG(error, "Unsupport packet type.");
	//	break;
	//}
}

void AServerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	NetDriver->Tick(DeltaSeconds);

	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	//{
	//	RequestEngineExit("Test");
	//}
}
//
AServerGameMode::AServerGameMode()
{

}

AServerGameMode::~AServerGameMode()
{
	
}