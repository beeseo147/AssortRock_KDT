#include "UObject/UObject.h"

UObjectBase::UObjectBase(UClass* InClass,EObjectFlags InObjectFlags,UObject* InOuter)
    : ObjectFlags(InObjectFlags)
    , ClassPrivate(InClass)
    , OuterPrivate(InOuter)
{

}