#pragma once
#include "CoreTypes.h"

struct FMemoryPool
{
public:
    void Create(const string_view InTypeName,const uint64 InSizePerOne);
    void* Malloc();
    void Free(void* InAddress);
    void Destroy();
private:
    string_view TypeName;
    uint64 SizePerOne;
    boost::pool<>* Pool = nullptr;
};

class CORE_API FUObjectArray
{
public:
    void Create(const type_info& InTypeInfo,const uint64 InSizePerOne);
    void* Malloc(const type_info& InTypeInfo);
    void Free(const type_info& InTypeInfo,void* InAdress);
    void Destroy();
private:
    unordered_map<HashKey,FMemoryPool> MapMemoryPool;
};

extern CORE_API FUObjectArray GUObjectArray;