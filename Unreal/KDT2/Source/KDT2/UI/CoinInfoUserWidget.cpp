// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CoinInfoUserWidget.h"
#include "Actors/GameState/CoinGameStateBase.h"

void UCoinInfoUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(RemainCoinText))
	{
		ensure(false);
		return;
	}

	RemainCoinText->TextDelegate.BindDynamic(this, &ThisClass::OnCoinTextChange);
	RemainCoinText->SynchronizeProperties();
}

FText UCoinInfoUserWidget::OnCoinTextChange()
{
	ACoinGameStateBase* GameState = Cast<ACoinGameStateBase>(GWorld->GetGameState());
	const uint32 RemainCoinNum = GameState->GetRemainCoinNum();
	const FText Text = FText::Format(NSLOCTEXT("Dumy", "Key", "Remain Coin: {0}"), RemainCoinNum);
	return Text;
}
