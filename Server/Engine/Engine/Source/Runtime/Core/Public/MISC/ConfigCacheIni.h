#pragma once
#include "CoreTypes.h"
#include "ConfigFile.h"
class CORE_API FConfigCacheIni
{
	
public:
	static void InitializeConfigSystem();
	static void DestroyConfigSystem();
public:
	bool LoadIniFile(FStringView InKey,const FString& InIniFileName,const bool bTryOverride = false);
	FConfigFile GetConfig(FStringView InKey) ;

private:
	map<FString, FConfigFile> MapCachedConfig;
};

extern CORE_API FConfigCacheIni* GConfig;