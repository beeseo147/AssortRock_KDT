#pragma once
enum EInternal{EC_InternalUseOnlyConstructor};

enum EObjectFlags
{
    RF_NoFlags = 0x00000000,

    RF_ClassDefaultObject = 0x00000010,

    RF_Class = 0x00000020
};

#define DEFINE_DEFAULT_CONSTRUCTOR_CALL(TClass) \
	static void __DefaultConstructor(const FObjectInitializer& X) { new((EInternal*)X.GetObj())TClass; }

#define DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(TClass) \
	static void __DefaultConstructor(const FObjectInitializer& X) { new((EInternal*)X.GetObj())TClass(X); }

#define GENERATED_BODY()
#define UCLASS(...)
#define UPROPERTY()
//#define UFUNCTION()

// DLL export and import definitions
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)