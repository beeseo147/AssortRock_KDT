#include "LaunchEngineLoop.h"

//특정 위치에서만 참조하기 위하여
extern CORE_API map<FString, UClass*> MapClass;

class LAUNCH_API UTest : public UObject
{
public:
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UTest);
	//static void __DefaultConstructor(const FObjectInitializer& X) { new((EInternal*)X.GetObj())UTest; }
	UTest() {};
	int a = 0;
};

int32 FEngineLoop::PreInit(const TCHAR* CmdLine)
{
	GetPrivateStaticClassBody<UTest>(TEXT("UTest")
		, InternalConstructor<UTest>, nullptr, nullptr);

	UClass* Class = MapClass[TEXT("UTest")];
	Class->GetDefaultObject(true);
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
