#pragma once
// AssortRock Inc.

#include "EngineMinimal.h"
#include "ServerGameInstance.generated.h"

UCLASS()
class SERVERPROJECT_API UServerGameInstance : public UGameInstance
{
	GENERATED_BODY();

public:
	virtual void Initailize() override;
	virtual void StartGameInstance() override;

	UServerGameInstance();
	~UServerGameInstance();
};