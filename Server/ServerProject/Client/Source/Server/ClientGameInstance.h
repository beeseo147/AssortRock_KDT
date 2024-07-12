#pragma once
// AssortRock Inc.

#include "EngineMinimal.h"
#include "ClientGameInstance.generated.h"

UCLASS()
class CLIENTPROJECT_API UClientGameInstance : public UGameInstance
{
	GENERATED_BODY();

public:
	virtual void Initailize() override;
	virtual void StartGameInstance() override;

	UClientGameInstance();
	~UClientGameInstance();
};