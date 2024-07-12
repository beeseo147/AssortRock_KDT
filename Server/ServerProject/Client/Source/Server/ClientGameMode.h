#pragma once
// AssortRock Inc.

#include "EngineMinimal.h"
#include "NetworkMinimal.h"
#include "ClientGameMode.generated.h"

enum class EMyPacketType : uint32
{
	EStart = FPacketHeader::EEnd,
	EMessage,
};

struct FMessagePacket : public FPacketHeader
{
	FMessagePacket() :
		FPacketHeader((uint32)EMyPacketType::EMessage, sizeof(FMessagePacket) - sizeof(FPacketHeader)) {}
	array<char, 1024> Buffer = {};
};

UCLASS()
class CLIENTPROJECT_API AClientGameMode : public AGameModeBase
{
	GENERATED_BODY();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds);

	AClientGameMode();
	~AClientGameMode();

	shared_ptr<UNetDriver> NetDriver;
};