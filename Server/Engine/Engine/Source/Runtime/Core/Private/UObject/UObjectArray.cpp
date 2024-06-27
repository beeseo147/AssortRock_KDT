#include "UObject/UObjectArray.h"

CORE_API FUObejctArray GUObjectArray;

void FMemoryPool::Create(const string_view InTypeName, const uint64 InSizePerOne)
{
    if(Pool)
    {
        //이미 Pool이 있다.
        _ASSERT(false);
        return;
    }

    TypeName = InTypeName;
    SizePerOne = InSizePerOne;
    Pool = new boost::pool<>(SizePerOne);
}

void *FMemoryPool::Malloc()
{
    void* Address = Pool->malloc();
    return nullptr;
}

void FMemoryPool::Free(void *InAddress)
{
    Pool->free(InAddress);
}

void FMemoryPool::Destroy()
{
    if (Pool)
    {
        delete Pool;
        Pool = nullptr;
    }
}

void FUObjectArray::Create(const type_info &InTypeInfo, const uint64 InSizePerOne)
{
    MapMemoryPool[InTypeInfo.hash_code()].Create(InTypeInfo.name(),InSizePerOne);
}

void * FUObjectArray::Malloc(const type_info &InTypeInfo)
{
    MapMemoryPool[InTypeInfo.hash_code()].Malloc();
}

void FUObjectArray::Free(const type_info &InTypeInfo, void *InAdress)
{
    MapMemoryPool[InTypeInfo.hash_code()].Free(InAdress);
}

void FUObjectArray::Destroy()
{
    for (auto& It : MapMemoryPool)
    {
        It.second.Destroy();
    }
    MapMemoryPool.clear();
}
