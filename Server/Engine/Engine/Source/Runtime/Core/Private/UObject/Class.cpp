#include "UObject/Class.h"
#include "UObject/UObjectArray.h"

UClass::UClass(FStringView InClassName,const type_info& InClassTypeInfo,
            const uint64 InClassSize,ClassConstructorType InClassConstructor,
            StaticClassFunctionType InSuperClassFunction)
            : SuperClass(nullptr)
            , ClassDefaultObject(nullptr)
            , ClassName(InClassName)
            , ClassTypeInfo(InClassTypeInfo)
            , ClassSize(InClassSize)
            , ClassConstructor(InClassConstructor)
{
    if(InSuperClassFunction)
    {
        SuperClass = InSuperClassFunction();
    }
}

CORE_API void UClass::InternalCreateDefaultObjectWrapper() const
{
    const_cast<UClass*>(this)->CreateDefaultObject();
}

CORE_API UObject* UClass::CreateDefaultObject()
{
    _ASSERT(!ClassDefaultObject);

    const uint64 SharedPtrSize = sizeof(_Ref_count_obj_alloc3<UObject, std::allocator<UObject>>);
    GUObjectArray.Create(ClassTypeInfo,SharedPtrSize+ClassSize);

    return ClassDefaultObject;
}