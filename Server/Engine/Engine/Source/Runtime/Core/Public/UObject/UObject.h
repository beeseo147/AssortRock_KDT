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

    template <typename ClassType>
    static FORCEINLINE bool IsChildOfWorkaround(const ClassType* ObjClass, const ClassType* TestCls)
    {
        return ObjClass->IsChildOf(TestCls);
    }

    template<class OtherClassType>
    FORCEINLINE bool IsA(OtherClassType SomeBase) const
    {
        // We have a cyclic dependency between UObjectBaseUtility and UClass,
        // so we use a template to allow inlining of something we haven't yet seen, because it delays compilation until the function is called.

        // 'static_assert' that this thing is actually a UClass pointer or convertible to it.
        const UClass* SomeBaseClass = SomeBase;
        (void)SomeBaseClass;
        //checkfSlow(SomeBaseClass, TEXT("IsA(NULL) cannot yield meaningful results"));

        const UClass* ThisClass = GetClass();

        // Stop the compiler doing some unnecessary branching for nullptr checks
        //UE_ASSUME(SomeBaseClass);
        //UE_ASSUME(ThisClass);

        return IsChildOfWorkaround(ThisClass, SomeBaseClass);
    }

    /** Returns true if this object is of the template type. */
    template<class T>
    bool IsA() const
    {
        return IsA(T::StaticClass());
    }

    static UClass* StaticClass() { return nullptr; }

    bool HasAnyFlags(const EObjectFlags FlagToCheck) const
    {
        return (GetFlags() & FlagToCheck);
    }
    
    const FString& GetName() { return Name; }
    
    FString Name;
};