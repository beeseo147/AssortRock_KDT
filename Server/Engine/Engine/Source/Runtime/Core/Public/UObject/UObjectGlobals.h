#pragma once
#include "CoreTypes.h"


FORCEINLINE bool CORE_API IsEngineExitRequested();

void CORE_API RequestEngineExit(const string ReasonString);

class UClass;
class UObject;
struct CORE_API FStaticConstructObjectParameters
{
	UClass* Class = nullptr;
	UObject* Outer = nullptr;
	FString Name;
	EObjectFlags SetFlags = RF_NoFlags;

	FStaticConstructObjectParameters(UClass* InClass);

};
struct CORE_API FObjectInitializer
{
    UClass* Class = nullptr;
    EObjectFlags ObjectFlags = EObjectFlags::RF_NoFlags;


    UObject* OuterPrivate = nullptr;
    FString Name;

    UObject* GetObj()const { return Obj; }

    FObjectInitializer() {}
    FObjectInitializer(const EObjectFlags InObjectFlags);
    FObjectInitializer(const FStaticConstructObjectParameters& StaticConstructObjectParam);

    //FObjectInitializer를 사용하여 신규로 만들어진 UObject객체
    shared_ptr<UObject> SharedObj;

    //FAllocator 내부에서 MemoryPool로부터 shared_ptr 크기를 고려해서 계산된 주소
    UObject* Obj = nullptr;

};

CORE_API shared_ptr<UObject> StaticConstructorObject_Internal(FStaticConstructObjectParameters& Params);

template <typename T>
shared_ptr<T> NewObject(UObject* Outer, UClass* InClass = nullptr, FString Name = NAME_NONE,EObjectFlags Flag = RF_NoFlags)
{
    if(!InClass)
    {
        InClass = T::StaticClass();
    }
    FStaticConstructObjectParameters Params(InClass);
    Params.Outer = Outer;
    Params.Name = Name;
    Params.SetFlags = Flag;

    return Cast<T>(StaticConstructorObject_Internal(Params));
}
template< class T >
inline const T* GetDefault()
{
    return (const T*)T::StaticClass()->GetDefaultObject();
}