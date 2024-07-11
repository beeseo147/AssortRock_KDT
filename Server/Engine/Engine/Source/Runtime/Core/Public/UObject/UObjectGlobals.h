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

// wstring -> UTF8
CORE_API string to_string(const FString& InString);
// wstring -> UTF8
CORE_API string to_string(FStringView InString);
// UTF8 -> wstring
CORE_API FString to_wstring(const string& InString);
// UTF8 -> wstring
CORE_API FString to_wstring(string_view InString);

CORE_API uint64 operator""_hash(const ANSICHAR * NewString, size_t);
CORE_API uint64 operator""_hash(const WIDECHAR * NewString, size_t);
CORE_API uint64 Hash(const ANSICHAR* NewString);
CORE_API uint64 Hash(const WIDECHAR* NewString);

template< class T >
inline const T* GetDefault()
{
    return (const T*)T::StaticClass()->GetDefaultObject();
}