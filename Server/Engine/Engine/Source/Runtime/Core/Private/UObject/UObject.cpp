#include "UObject/UObject.h"




UObjectBase::UObjectBase(UClass* InClass,EObjectFlags InObjectFlags,UObject* InOuter)
    : ObjectFlags(InObjectFlags)
    , Class(InClass)
    , OuterPrivate(InOuter)
{

}