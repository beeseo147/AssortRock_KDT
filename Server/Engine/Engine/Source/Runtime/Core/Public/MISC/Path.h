#pragma once
#include "CoreTypes.h"

class CORE_API FPaths
{
public:
	static const FString& EngineDir();
	static const FString& EngineConfigDir();
	static const FString& ProjectDllDir();
};