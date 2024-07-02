#include "UObject/Class.h"
#include "UObject/UObjectArray.h"

CORE_API map<FString, UClass*> MapClass;

UClass::UClass(FString InClassName,const type_info& InClassTypeInfo,
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

UObject* UClass::GetDefaultObject(bool bNoCreate) const
{
    if (ClassDefaultObject == nullptr && !bNoCreate)
    {
        //CDO를 만든다
        InternalCreateDefaultObjectWrapper();
    }
    return ClassDefaultObject.get();
}


CORE_API void UClass::InternalCreateDefaultObjectWrapper() const
{
    //상속성을 제거하기 위한 const_cast
    const_cast<UClass*>(this)->CreateDefaultObject();
}

CORE_API UObject* UClass::CreateDefaultObject()
{
    _ASSERT(!ClassDefaultObject);

    const uint64 SharedPtrSize = sizeof(_Ref_count_obj_alloc3<UObject, std::allocator<UObject>>);
    GUObjectArray.Create(ClassTypeInfo, SharedPtrSize + ClassSize);

    FStaticConstructObjectParameters StaticConstuctObjectParameter{this};

    FObjectInitializer ObjectInitializer{ StaticConstuctObjectParameter };
    ClassConstructor(ObjectInitializer);

    ClassDefaultObject = ObjectInitializer.SharedObj;


    return ClassDefaultObject.get();
}

CORE_API UClass* RegisterEngineClass(FString InClassName, UClass::ClassConstructorType InClassConstructor, UClass::StaticClassFunctionType InSuperClassFunction, function<void()> InClassReflection, const type_info& InClassTypeInfo, const uint64 InClassSize)
{
    GUObjectArray.Create(typeid(UClass), sizeof(UClass));
    UObjectBase * ObjectBase = (UObjectBase*)GUObjectArray.Malloc(typeid(UClass));
    
    new(ObjectBase) UObjectBase(nullptr, EObjectFlags::RF_Class,nullptr);
    
    UClass* NewClass = new(ObjectBase) UClass(InClassName, InClassTypeInfo, InClassSize, InClassConstructor, InSuperClassFunction);
    NewClass->ClassName = TEXT("UClass");

    MapClass.insert(make_pair(InClassName, NewClass));
    return NewClass;
}
