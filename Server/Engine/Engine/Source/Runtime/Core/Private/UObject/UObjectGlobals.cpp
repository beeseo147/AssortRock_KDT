#include "UObject/UObjectGlobals.h"
#include "UObject/Class.h"
#include "Logging/Logger.h"

bool GIsRequestingExit = false; /* Indicates that MainLoop() should be exited at the end of the current iteration */

bool CORE_API IsEngineExitRequested()
{
	return GIsRequestingExit;
}

void CORE_API RequestEngineExit(const string ReasonString)
{
	E_Log(trace, "%s", ReasonString.c_str());
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
