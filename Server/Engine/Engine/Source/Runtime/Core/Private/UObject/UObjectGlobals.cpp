#include "UObject/UObjectGlobals.h"
#include "UObject/Class.h"
#include "Logging/Logger.h"
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
