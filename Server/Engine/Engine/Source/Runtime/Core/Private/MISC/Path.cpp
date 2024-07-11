#include "MISC/Path.h"

const FString& FPaths::EngineDir()
{
	static const FString Path = filesystem::current_path();
	return Path;
}

const FString& FPaths::EngineConfigDir()
{
	static const FString Path = EngineDir() + TEXT("\\Config");
	return Path;
}

const FString& FPaths::ProjectDllDir()
{
	static const FString Path = EngineDir() + TEXT("\\Project");
	return Path;
}
