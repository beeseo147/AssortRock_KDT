#pragma once
#include "UObject.h"
#include "UObjectArray.h"
/**
 *  An object class.
 */

class UClass : public UObject
{
public:
    CORE_API static UClass* FindClass(FStringView InClassName);

private:
    UClass* SuperClass;
    shared_ptr<UObject> ClassDefaultObject;

public:
    FString ClassName; 
    const type_info& ClassTypeInfo;
    const uint64 ClassSize;
    //함수 포인터의 지정
    using ClassConstructorType = function<void(const FObjectInitializer&)>;
    ClassConstructorType ClassConstructor;

    using StaticClassFunctionType = function<UClass*(void)>;

    UClass() = delete;
    CORE_API UClass(FString InClassName, const type_info& InClassTypeInfo,
        const uint64 InClassSize, ClassConstructorType InClassConstructor,
        StaticClassFunctionType InSuperClassFunction);
    ~UClass() {}
    UClass* GetSuperClass() const {return SuperClass;}

    template<class T>
    T* GetDefaultObject(){return (T*)GetDefaultObject();}

    CORE_API UObject* GetDefaultObject(bool bNoCreate = true) const;

    template<class T>
    bool IsChildOf() const{return IsChildOf(T::StaticClass());}
    
    CORE_API bool IsChildOf(const UClass* SomeBase) const;


protected:
    CORE_API void InternalCreateDefaultObjectWrapper() const;
    CORE_API UObject* CreateDefaultObject();

private:
    /**
     * This signature intentionally hides the method declared in UObjectBaseUtility to make it private.
     * Call IsChildOf instead; Hidden because calling IsA on a class almost always indicates an error where the caller should use IsChildOf
     */
    bool IsA(const UClass* Parent) const
    {
        return UObject::IsA(Parent);
    }
};

CORE_API UClass* RegisterEngineClass(
    FString InClassName,
    UClass::ClassConstructorType InClassConstructor,
    UClass::StaticClassFunctionType InSuperClassFunction,
    function<void()> InClassReflection,
    const type_info& InClassTypeInfo,
    const uint64 InClassSize
);

template<class T>
UClass* GetPrivateStaticClassBody(
    FString InClassName,
    UClass::ClassConstructorType InClassConstructor,
    UClass::StaticClassFunctionType InSuperClassFunction,
    function<void()> InClassReflection)
{
    const type_info& ClassTypeInfo = typeid(T);
    const uint64 ClassSize = sizeof(T);

    UClass* NewClass = RegisterEngineClass(InClassName, InClassConstructor,
        InSuperClassFunction, InClassReflection, ClassTypeInfo, ClassSize);
    return NewClass;
}


template<class T>
void InternalConstructor(const FObjectInitializer& X)
{
    FObjectInitializer* ObjectInitializer = const_cast<FObjectInitializer*>(&X);
    ObjectInitializer->SharedObj = allocate_shared<T>(FAllocator<T>(ObjectInitializer));
}