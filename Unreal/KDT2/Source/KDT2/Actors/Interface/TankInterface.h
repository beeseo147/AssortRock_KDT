#pragma once

#include "CoreMinimal.h"
#include "TankInterface.generated.h"

UINTERFACE()
class UTankInterface : public UInterface
{
	GENERATED_BODY()
};

class ITankInterface
{
	GENERATED_BODY()

public:
	virtual void ZoomIn() = 0;
	virtual void ZoomOut() = 0;
	virtual void Fire() = 0;
};