// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CoinGameStateBase.generated.h"

class UCoinInfoUserWidget;
struct FCoinDataTableRow;

UCLASS()
class KDT2_API ACoinGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ACoinGameStateBase();
	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void GetCoin(const FCoinDataTableRow* InCoinDataTableRow);
	uint32 GetRemainCoinNum() const { return RemainCoinNum; }

private:
	TSubclassOf<UCoinInfoUserWidget> CoinWidgetClass;
	UCoinInfoUserWidget* CoinInfoWidget;
	uint32 RemainCoinNum = 0;

	FTimerHandle LevelTransitionTimerHandle;
};
