#pragma once
// AssortRock Inc.

#include "EngineMinimal.h"
#include "ProjectGameMode.generated.h"

UCLASS()
class GAMEPROJECT_API AProjectGameMode : public AGameModeBase
{
	GENERATED_BODY();

public:
	virtual void BeginPlay() override;

	AProjectGameMode();
	~AProjectGameMode();
};