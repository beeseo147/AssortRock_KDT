#include "Engine/World.h"
#include "Engine/GameInstance.h"
UWorld::UWorld()
{

}

UWorld::~UWorld()
{
	
}

void UWorld::Tick(float DeltaSeconds)
{
	for (auto It : MapActors)
	{
		It.second->Tick(DeltaSeconds);
	}
}

void UWorld::SetGameInstance(engine_weak_ptr<UGameInstance> NewGI)
{
	OwningGameInstance = NewGI;
}

void UWorld::SetGameMode(TSubclassOf<AGameModeBase> NewGameModeClass)
{
	if (GameMode.IsValid())
	{
		E_Log(fatal, "GameMode Is vaild");
		return;
	}

	GameMode = SpawnActor<AGameModeBase>(NewGameModeClass);

}

engine_weak_ptr<AActor> UWorld::SpawnActor(UClass* InClass, const FActorSpawnParameters& SpawnParameters)
{
	if (!InClass)
	{
		E_Log(error, "Class is nullptr");
	}
	shared_ptr<AActor> NewActor = NewObject<AActor>(this, InClass, SpawnParameters.Name, SpawnParameters.Object);
	FString ActorName = NewActor->GetName();
	MapActors.insert(make_pair(ActorName, NewActor));
	
	NewActor->BeginPlay();

	return NewActor;
}
