#pragma once
#include "CoreTypes.h"
#include "Logging/Logger.h"
#include "UObject/UObjectGlobals.h"
class CORE_API FConfigFile
{
public:
	bool Load(FStringView InPath);
	bool TryOverride(FStringView InPath);

public:
	template<class T>
	bool Get(const ANSICHAR* InSection, const ANSICHAR* InKey, T& OutValue)
	{
		ini::IniField Field;
		bool bFind = Get(InSection, InKey, Field);
		if (!bFind)
		{
			E_Log(error, "Get failed {}, {}", InSection, InKey);
			return false;
		}

		OutValue = Field.as<T>();
		return true;
	}

	template<>
	bool Get(const ANSICHAR* InSection, const ANSICHAR* InKey, FString& OutValue)
	{
		string String;
		if (!Get<string>(InSection, InKey, String))
		{
			return false;
		}

		OutValue = to_wstring(String);
		return true;
	}

private:
	bool Get(const ANSICHAR* InSection, const ANSICHAR* InKey, ini::IniField& OutFiled);
	bool Get(ini::IniFile& InTarget, const ANSICHAR* InSection, const ANSICHAR* InKey, ini::IniField& OutFiled);
private:
	bool bLoaded = false;
	bool bOverride = false;


	ini::IniFile File;
	ini::IniFile OverrideFile;
};