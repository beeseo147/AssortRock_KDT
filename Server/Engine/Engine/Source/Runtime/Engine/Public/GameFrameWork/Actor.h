#pragma once
// AssortRock Inc.

#include "CoreMinimal.h"
#include "Actor.generated.h"

UCLASS()
class ENGINE_API AActor : public UObject
{
	GENERATED_BODY();

public:
	AActor();
	~AActor();

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);
};