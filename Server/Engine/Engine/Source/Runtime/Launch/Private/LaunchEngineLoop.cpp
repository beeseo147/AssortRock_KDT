#include "LaunchEngineLoop.h"

//특정 위치에서만 참조하기 위하여
extern CORE_API map<FString, UClass*> MapClass;

class LAUNCH_API UTest : public UObject
{
public:
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UTest);
	static UClass* StaticClass() {
		return UTestRegisterEngineClass;
	}

	static inline UClass* UTestRegisterEngineClass= GetPrivateStaticClassBody<UTest>(TEXT("UTest")
		, InternalConstructor<UTest>, &UObject::StaticClass, nullptr);

	UTest() {};
	int a = 0;
};

int32 FEngineLoop::PreInit(const TCHAR* CmdLine)
{
	UClass* Class = MapClass[TEXT("UTest")];
	UObject* Object = Class->GetDefaultObject(false);
	
	for (auto& It : MapClass)
	{
		It.second->GetDefaultObject(false);
	}
	UClass* UTestClass = MapClass[TEXT("UTest2")];
	UTestClass->IsChildOf<UTest>();
	return 0;
}

int32 FEngineLoop::Init()
{
	return 0;
}

void FEngineLoop::Tick()
{
}

void FEngineLoop::Exit()
{
	for (auto& It : MapClass)
	{
		It.second->~UClass();
		GUObjectArray.Free(typeid(UClass), It.second);
	}
	
}
