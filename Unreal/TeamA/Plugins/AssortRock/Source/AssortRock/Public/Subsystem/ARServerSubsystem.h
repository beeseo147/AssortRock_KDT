// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NetWork/ARNetDriver.h"
#include "ARServerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ASSORTROCK_API UARServerSubsystem : public UGameInstanceSubsystem , public FARNetworkNotify
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
protected: // FARNetworkNotify
	virtual void NotifyConnect(UARNetConnection* Connection) override;
	virtual void NotifyConnectionClosed(UARNetConnection* Connection) override;
	virtual void NotifyReceivedRawPacket(UARNetConnection* Connection, FARPacketHeader* Packet) override;
	// FARNetworkNotify end
protected:
	UPROPERTY(Transient)
	UARNetDriver* ARNetDriver = nullptr; 
};
