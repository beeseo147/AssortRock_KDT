// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameState/CoinGameStateBase.h"
#include "UI/CoinInfoUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Coin/Coin.h"

ACoinGameStateBase::ACoinGameStateBase()
{
	static ConstructorHelpers::FClassFinder<UCoinInfoUserWidget> FindClass
	{TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KDT2/Blueprint/Coin/UI_CoinInfo.UI_CoinInfo_C'")};

	ensure(FindClass.Class);
	CoinWidgetClass = FindClass.Class;
}

void ACoinGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoin::StaticClass(), Actors);
	RemainCoinNum = Actors.Num();

	CoinInfoWidget = CreateWidget<UCoinInfoUserWidget>(GetWorld(), CoinWidgetClass);
	CoinInfoWidget->AddToViewport();
}

void ACoinGameStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(LevelTransitionTimerHandle);
}

void ACoinGameStateBase::GetCoin(const FCoinDataTableRow* InCoinDataTableRow)
{
	--RemainCoinNum;
	if (RemainCoinNum == 0)
	{
		auto TimerDelegate = [this]()
			{
				UGameplayStatics::OpenLevel(this, TEXT("LobbyMap"));
			};

		GetWorld()->GetTimerManager().SetTimer(LevelTransitionTimerHandle, TimerDelegate, 2.5f, false);
	}
}
