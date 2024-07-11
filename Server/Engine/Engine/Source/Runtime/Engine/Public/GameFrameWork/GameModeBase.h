﻿#pragma once
// AssortRock Inc.

#include "CoreMinimal.h"
#include "GameFrameWork/Actor.h"
#include "GameModeBase.generated.h"

UCLASS()
class ENGINE_API AGameModeBase : public AActor
{
	GENERATED_BODY();

public:
	AGameModeBase();
	~AGameModeBase();
};