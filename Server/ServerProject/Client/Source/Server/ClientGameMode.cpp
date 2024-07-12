#include "ClientGameMode.h"

void AClientGameMode::BeginPlay()
{
	Super::BeginPlay();

	NetDriver = NewObject<UNetDriver>(this);
	FNetworkNotify NetworkNotify(
		[this](UNetDriver* InNetDriver, UNetConnection* NetConnection)
		{
			FMessagePacket MessagePacket;

			string Test = "Hello Server";
			strcpy(&MessagePacket.Buffer[0], Test.c_str());
			InNetDriver->Send(InNetDriver->GetClientConnection().Get(), &MessagePacket);
		},
		[this](UNetDriver*, UNetConnection*)
		{
		},
		[this](UNetDriver*, UNetConnection*, FPacketHeader* PacketHeader)
		{
			EMyPacketType PacketType = (EMyPacketType)PacketHeader->GetPacketID();
			if (PacketType == EMyPacketType::EMessage)
			{
				FMessagePacket* MessagePacket = (FMessagePacket*)PacketHeader;
				string Message = string(MessagePacket->Buffer.begin(), MessagePacket->Buffer.end());
				E_Log(trace, "{}", Message);
			}
		});
	FURL URL;
	if (!NetDriver->InitConnect(NetworkNotify, URL))
	{
		RequestEngineExit("Connect failed");
		return;
	}
}

void AClientGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	NetDriver->Tick(DeltaSeconds);
	//RequestEngineExit("");
}

AClientGameMode::AClientGameMode()
{

}

AClientGameMode::~AClientGameMode()
{
	
}