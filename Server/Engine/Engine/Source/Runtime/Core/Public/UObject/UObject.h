#pragma once
#include "CoreTypes.h"

class UClass;
class UObject;

struct CORE_API FObjectInitializer
{
    UClass* Class = nullptr;
    EObjectFlags ObjectFlags = EObjectFlags::RF_NoFlags;


    UObject* OuterPrivate = nullptr;
    FString Name;

    FObjectInitializer(){}
    FObjectInitializer(const EObjectFlags InObjectFlags);
};
class CORE_API UObjectBase : public std::enable_shared_from_this<UObject>
{
    UObjectBase(){}
    UObjectBase(UClass* InClass,EObjectFlags InObjectFlags,UObject* InOuter);
    virtual ~UObjectBase();

    EObjectFlags GetFlags() const {return ObjectFlags;}
    UObject* GetOuter() const {return OuterPrivate;}
    UClass* GetClass() const { return Class; }

protected:
    EObjectFlags ObjectFlags;

     UClass* Class = nullptr;
     UObject* OuterPrivate = nullptr;
};

class CORE_API UObject : public UObjectBase
{
public:
    UObject(){}

    bool HasAnyFlags(const EObjectFlags FlagToCheck) const
    {
        return (GetFloags() & FlagToCheck);
    }
    
};