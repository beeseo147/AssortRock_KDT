#pragma once
// AssortRock Inc.

#include "CoreMinimal.h"
#include "GameInstance.generated.h"

class UEngine;
UCLASS()
class ENGINE_API UGameInstance : public UObject
{
	GENERATED_BODY();
public:
	void Initialize();
	void StartGameInstance();

	UEngine* GetEngine();
public:
	UGameInstance();
	~UGameInstance();

	// weak_ptr<World>
	engine_weak_ptr<class UWorld> World;
};