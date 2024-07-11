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
	virtual void Initialize();
	virtual void StartGameInstance();

	UEngine* GetEngine();
public:
	UGameInstance();
	~UGameInstance();

	// weak_ptr<World>
	UPROPERTY()
	engine_weak_ptr<class UWorld> World;
};