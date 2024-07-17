#pragma once
 //AssortRock Inc.

#include "EngineMinimal.h"
#include "NetworkMinimal.h"
#include "ServerGameMode.generated.h"

//enum class EARPacketType : uint32
//{
//	EStart = FPacketHeader::EEnd,
//	EMessage,
//
//	ELogin,
//};

//struct FMessagePacket : public FPacketHeader
//{
//	FMessagePacket() :
//		FPacketHeader((uint32)EARPacketType::EMessage, sizeof(FMessagePacket) - sizeof(FPacketHeader)) {}
//	array<char, 1024> Buffer = {};
//};


//struct FAccountPacket : public FPacketHeader
//{
//	std::array<char, 20> ID = {};
//	std::array<char, 20> Password = {};
//};

UCLASS()
class SERVERPROJECT_API AServerGameMode : public AGameModeBase
{
	GENERATED_BODY();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds);

	void OnRecv(UNetDriver* InNetDriver, UNetConnection* InNetConnection, FPacketHeader* InPacketHeader);

	AServerGameMode();
	~AServerGameMode();

	shared_ptr<UNetDriver> NetDriver;
};