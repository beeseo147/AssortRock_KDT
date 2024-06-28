#pragma once
#include "CoreTypes.h"

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

    shared_ptr<UObject> GetObj()const { return Obj; }

    FObjectInitializer() {}
    FObjectInitializer(const EObjectFlags InObjectFlags);
    FObjectInitializer(const FStaticConstructObjectParameters& StaticConstructObjectParam);

private:
    //FObjectInitializer를 사용하여 신규로 만들어진 UObject객체
    shared_ptr<UObject> Obj;
};