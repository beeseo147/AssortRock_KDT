#pragma once
#include "CoreMinimal.h"
#include "StatusInterface.generated.h"

UCLASS()
class UStatusBase : public UObject
{
	GENERATED_BODY()

public:
	UStatusBase()
	{
		UE_LOG(LogTemp, Warning, TEXT("UStatusBase()"));
	}
	~UStatusBase()
	{
		UE_LOG(LogTemp, Warning, TEXT("~UStatusBase()"));
	}
	float HP = 3;
};

UCLASS()
class UStatusBase2 : public UStatusBase
{
	GENERATED_BODY()

public:
	UStatusBase2()
	{
		UE_LOG(LogTemp, Warning, TEXT("UStatusBase()"));
	}
	~UStatusBase2()
	{
		UE_LOG(LogTemp, Warning, TEXT("~UStatusBase()"));
	}
	float MP = 3;
};

UINTERFACE()
class UStatusInterface : public UInterface
{
	GENERATED_BODY()
};

class IStatusInterface
{
	GENERATED_BODY()
public:
	virtual TSubclassOf<UStatusBase> GetStatusClass()
	{
		return UStatusBase::StaticClass();
	}
};