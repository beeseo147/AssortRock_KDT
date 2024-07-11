#include "UObject/UObjectGlobals.h"
#include "UObject/Class.h"
#include "Logging/Logger.h"

bool GIsRequestingExit = false; /* Indicates that MainLoop() should be exited at the end of the current iteration */

bool IsEngineExitRequested()
{
	return GIsRequestingExit;
}

void CORE_API RequestEngineExit(const string ReasonString)
{
	E_Log(trace, "{}", ReasonString.c_str());
	GIsRequestingExit = true;
}

FStaticConstructObjectParameters::FStaticConstructObjectParameters(UClass* InClass)
	: Class(InClass)
{
	if (!Class)
	{
		E_Log(error,"Class Is nullptr")
	}
	
}

FObjectInitializer::FObjectInitializer(const EObjectFlags InObjectFlags)
	:ObjectFlags(InObjectFlags)
{

}

FObjectInitializer::FObjectInitializer(const FStaticConstructObjectParameters& StaticConstructObjectParam)
	: Class(StaticConstructObjectParam.Class)
	, OuterPrivate(StaticConstructObjectParam.Outer)
	, ObjectFlags(StaticConstructObjectParam.SetFlags)
	, Name(StaticConstructObjectParam.Name)
{
}

CORE_API shared_ptr<UObject> StaticConstructorObject_Internal(FStaticConstructObjectParameters& Params)
{
	UClass* InClass = Params.Class;
	FString& InName = Params.Name;

	if (InName == NAME_NONE)
	{ 
		static map<FString, int64> NameCountMap;
		FString ClassName = InClass->ClassName;
		int64& NewIndex = NameCountMap[ClassName];

		InName = ClassName + TEXT("_") + to_wstring(NewIndex);
		
		++NewIndex;
	}

	FObjectInitializer ObjectInitializer{ Params };

	if (ObjectInitializer.ObjectFlags & EObjectFlags::RF_ClassDefaultObject)
	{
		E_Log(fatal, "Detected ObjectFlags & RF_ClassDefaultObject");
	}

	InClass->ClassConstructor(ObjectInitializer);

	return ObjectInitializer.SharedObj;
}

CORE_API string to_string(const FString& InString)
{
	// wstring -> UTF8
	return wstring_convert<codecvt_utf8<WIDECHAR>>().to_bytes(InString);
}

CORE_API string to_string(FStringView InString)
{
	// wstring -> UTF8
	return wstring_convert<codecvt_utf8<WIDECHAR>>().to_bytes(InString.data());
}

CORE_API FString to_wstring(const string& InString)
{
	// UTF8 -> wstring
	return wstring_convert<codecvt_utf8<WIDECHAR>>().from_bytes(InString);
}

CORE_API FString to_wstring(string_view InString)
{
	// UTF8 -> wstring
	return wstring_convert<codecvt_utf8<WIDECHAR>>().from_bytes(InString.data());
}

CORE_API uint64 operator""_hash(const ANSICHAR * NewString, size_t)
{
	// 문자열을 Hash function에 넣으면 숫자가 나온다
	// 같은 문자열을 넣으면 같은 숫자가 난온다
	// Hash 충돌: 그러나 가끔 다른 문자열을 넣었을때 동일한 숫자가 나올수도 있다.
	static hash<string_view> HashFunction;
	return HashFunction(NewString);
}

CORE_API uint64 operator""_hash(const WIDECHAR * NewString, size_t)
{
	static hash<wstring_view> HashFunction;
	return HashFunction(NewString);
}

CORE_API uint64 Hash(const ANSICHAR* NewString)
{
	static hash<string_view> HashFunction;
	return HashFunction(NewString);
}

CORE_API uint64 Hash(const WIDECHAR* NewString)
{
	static hash<wstring_view> HashFunction;
	return HashFunction(NewString);
}