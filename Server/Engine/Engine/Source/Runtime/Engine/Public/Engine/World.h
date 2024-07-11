#pragma once
// AssortRock Inc.

#include "CoreMinimal.h"
#include "GameFrameWork/GameModeBase.h"
#include "World.generated.h"

class UGameInstance;
struct ENGINE_API FActorSpawnParameters
{
	FString Name;

	AActor* Owner = nullptr;

	EObjectFlags Object;
};
UCLASS()
class ENGINE_API UWorld : public UObject
{
	GENERATED_BODY();

public:
	UWorld();
	~UWorld();

	void Tick(float DeltaSeconds);

	void SetGameInstance(engine_weak_ptr<UGameInstance> NewGI);
	void SetGameMode(TSubclassOf<AGameModeBase> NewGameModeClass);

	engine_weak_ptr<AActor> SpawnActor(UClass* InClass, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters());

	template<class T>
	engine_weak_ptr<T> SpawnActor(UClass* InClass, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters())
	{
		return Cast<T>(SpawnActor(InClass, SpawnParameters));
	}

private:
	map<FString, shared_ptr<AActor>> MapActors;
private:
	engine_weak_ptr<UGameInstance> OwningGameInstance;
	engine_weak_ptr<AGameModeBase> GameMode;
};