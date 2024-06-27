#pragma once
#include "UObject.h"
/**
 *  An object class.
 */

class UClass : public UObject
{
private:
    UClass* SuperClass;
    UObject* ClassDefaultObject;

public:
    FStringView ClassName; 
    const type_info& ClassTypeInfo;
    const uint64 ClassSize;

    using ClassConstructorType = function<void(const FObjectInitializer&)>;
    ClassConstructorType ClassConstructor;

    using StaticClassFunctionType = function<UClass*(void)>;

    UClass() = delete;
    UClass(FStringView InClassName,const type_info& InClassTypeInfo,
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
    
    UClass* GetSuperClass() const {return SuperClass;}

    template<class T>
    T* GetDefaultObject(){return (T*)GetDefaultObject();}
    UObject* CORE_API GetDefaultObject(bool bNoCreate = true)const
    {
        if(ClassDefaultObject==nullptr && !bNoCreate)
        {
            //CDO를 만든다
            InternalCreateDefaultObjectWrapper();
        }
        return ClassDefaultObject;
    }
    template<class T>
    bool IsChildOf() const{return IsChildOf(T::StaticClass());}
    
    bool CORE_API IsChildOf(const UClass* SomeBase) const{return false;}
protected:
    CORE_API void InternalCreateDefaultObjectWrapper() const;
    CORE_API UObject* CreateDefaultObject();
};
