#pragma once
// AssortRock Inc.

#include "EngineMinimal.h"
#include "ProjectGameInstance.generated.h"

UCLASS()
class GAMEPROJECT_API UProjectGameInstance : public UGameInstance
{
	GENERATED_BODY();

public:
	virtual void Initialize() override;
	virtual void StartGameInstance() override;
	UProjectGameInstance();
	~UProjectGameInstance();
};