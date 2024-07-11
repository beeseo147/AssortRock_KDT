#include "Engine/GameInstance.h"
#include "Engine/Engine.h"

void UGameInstance::Initialize()
{
	// World 생성
	UEngine* Engine = GetEngine();
	Engine->World = NewObject<UWorld>(this);
	Engine->World->SetGameInstance(Cast<UGameInstance>(this));
	UGameInstance;
}

void UGameInstance::StartGameInstance()
{
	//World에 GameMode 등록
}

UEngine* UGameInstance::GetEngine()
{
	return (UEngine*)GetOuter();
}

UGameInstance::UGameInstance()
{

}

UGameInstance::~UGameInstance()
{
	
}