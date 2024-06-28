#pragma once
#include "CoreTypes.h"
#include "UObjectGlobals.h"
class UClass;
class UObject;
// 의도된 사항으로 일부 경고를 무시합니다.
#pragma warning(disable:26495)

class CORE_API UObjectBase : public std::enable_shared_from_this<UObject>
{
public:
    UObjectBase() {}
    UObjectBase(UClass* InClass, EObjectFlags InObjectFlags, UObject* InOuter);
    virtual ~UObjectBase() {}

    EObjectFlags GetFlags() const { return ObjectFlags; }
    UObject* GetOuter() const { return OuterPrivate; }
    UClass* GetClass() const { return Class; }

protected:
    EObjectFlags ObjectFlags;
    /** Object this object resides in. */
    UObject* OuterPrivate;
    UClass* Class;
};

class CORE_API UObject : public UObjectBase
{
public:
    UObject(){}

    bool HasAnyFlags(const EObjectFlags FlagToCheck) const
    {
        return (GetFlags() & FlagToCheck);
    }
    
};