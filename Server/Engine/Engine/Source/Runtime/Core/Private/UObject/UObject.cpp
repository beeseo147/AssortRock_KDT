#include "UObject/UObject.h"


FObjectInitializer::FObjectInitializer(const EObjectFlags InObjectFlags)
    :ObjectFlags(InObjectFlags)
{

}

UObjectBase::UObjectBase(UClass* InClass,EObjectFlags InObjectFlags,UObject* InOuter)
    : ObjectFlags(InObjectFlags),
    , OuterPrivate(InOuter)
    , Class(InClass)
{

}