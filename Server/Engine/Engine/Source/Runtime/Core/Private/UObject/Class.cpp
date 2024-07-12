#include "UObject/Class.h"
#include "UObject/UObjectArray.h"
#include "Logging/Logger.h"
CORE_API map<FString, UClass*> MapClass;

CORE_API UClass* UClass::FindClass(FStringView InClassName)
{
    auto It = MapClass.find(InClassName.data());
    if (It == MapClass.end())
    {
        E_Log(error, "Failed {}", to_string(InClassName));
        return nullptr;
    }

    return It->second;
}

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
        // CDO를 만든다
        InternalCreateDefaultObjectWrapper();
    }
    return ClassDefaultObject.get();
}


bool CORE_API UClass::IsChildOf(const UClass* SomeBase) const
{
    _ASSERT(this);
    if (!SomeBase)
    {
        return false;
    }
    bool bOldResult = false;
    for (const UClass* TempClass = this; TempClass; TempClass = TempClass->GetSuperClass())
    {
        if (TempClass == SomeBase)
        {
            bOldResult = true;
            break;
        }
    }

    return bOldResult;
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
    //Class에 InternalConstructor를 호출한다.
    ClassDefaultObject = ObjectInitializer.SharedObj;


    return ClassDefaultObject.get();
}

CORE_API UClass* RegisterEngineClass(FString InClassName,
    UClass::ClassConstructorType InClassConstructor,
    UClass::StaticClassFunctionType InSuperClassFunction,
    function<void()> InClassReflection,
    const type_info& InClassTypeInfo, const uint64 InClassSize)
{
    // Reflection 함수 호출
    InClassReflection();

    GUObjectArray.Create(typeid(UClass), sizeof(UClass));
    UObjectBase* ObjectBase = (UObjectBase*)GUObjectArray.Malloc(typeid(UClass));

    new(ObjectBase)UObjectBase(nullptr, EObjectFlags::RF_Class, nullptr);

    UClass* NewClass = new(ObjectBase)UClass(InClassName, InClassTypeInfo, InClassSize,
        InClassConstructor, InSuperClassFunction);

    MapClass.insert(make_pair(InClassName, NewClass));

    return NewClass;
}

CORE_API void UClass::LogReflectionData(UObject* InObject)
{
    UClass* Class = InObject->GetClass();
    E_Log(trace, "Class: {}, Object: {}", to_string(Class->GetName()), to_string(InObject->GetName()));

    type Type = resolve(Hash(Class->ClassName.data()));
    Type.data([&](meta::data Data)
        {
            Data.prop([&](meta::prop p)
                {
                    FProperty Prop = p.value().cast<FProperty>();
                    switch (Prop.PropertyType)
                    {
                    case T_POINTER:
                    {
                        void* Address = Data.get(handle(Type.GetNode(), InObject)).data();

                        break;
                    }
                    case T_SHARED_PTR:
                    {
                        engine_weak_ptr<UObject> actual = *(shared_ptr<UObject>*)Data.get(handle(Type.GetNode(), InObject)).data();
                        E_Log(trace, "{} [shared_ptr] class {}", Prop.Name, to_string(Class->ClassName));
                        break;
                    }
                    case T_WEAK_PTR:
                    {
                        weak_ptr<UObject> actual = *(weak_ptr<UObject>*)Data.get(handle(Type.GetNode(), InObject)).data();
                        E_Log(trace, "{} [weak_ptr] class {}", Prop.Name, to_string(Class->ClassName));
                        break;
                    }
                    case T_ENGINE_WEAK_PTR:
                    {
                        engine_weak_ptr<UObject> actual = *(engine_weak_ptr<UObject>*)Data.get(handle(Type.GetNode(), InObject)).data();
                        E_Log(trace, "{} [engine_weak_ptr] class {}", Prop.Name, to_string(Class->ClassName));
                        break;
                    }
                    case T_INT:
                        E_Log(trace, "{} [int] {}", Prop.Name, Data.get(handle(Type.GetNode(), InObject)).cast<int>());
                        break;
                    case T_FLOAT:
                        E_Log(trace, "{} [float] {}", Prop.Name, Data.get(handle(Type.GetNode(), InObject)).cast<float>());
                        break;
                    default:
                        break;
                    }
                });
        }
    );
}