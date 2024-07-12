#include "Engine/Engine.h"
#include "Engine/GameMapsSettings.h"
UEngine::UEngine(const FObjectInitializer& X)
{

}

void UEngine::Init()
{
	GameInstance = NewObject<UGameInstance>(this, GetDefault<UGameMapsSettings>()->GameInstanceClass);
	GameInstance->Initailize();
}

void UEngine::Start()
{
	GameInstance->StartGameInstance();
}

void UEngine::Tick(float DeltaSeconds)
{
	// World -> Tick
	World->Tick(DeltaSeconds);
}

void UEngine::PreExit()
{
}
