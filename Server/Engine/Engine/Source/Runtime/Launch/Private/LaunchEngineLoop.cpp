#pragma once
#include "LaunchEngineLoop.h"
#include "UObject/Class.h"
UEngine* GEngine = nullptr;
//특정 위치에서만 참조하기 위하여
extern CORE_API map<FString, UClass*> MapClass;

int32 FEngineLoop::PreInit(const TCHAR* /*CmdLine*/)
{
	// 설정 파일 로드
	FConfigCacheIni::InitializeConfigSystem();

	//User DLL을 Load
	const FString& ProjectDllDir = FPaths::ProjectDllDir();
	if (filesystem::is_directory(ProjectDllDir))
	{
		for (const auto& It : filesystem::directory_iterator(ProjectDllDir))
		{
			if (It.path().extension() == TEXT(".dll"))
			{
				LoadLibrary(It.path().c_str());
			}

		}
	}

	//Create CDO
	for (auto& It : MapClass)
	{

		It.second->GetDefaultObject(false);
	}
	
	// User DLL을 Load

	return 0;
}

int32 FEngineLoop::Init()
{
	Engine = NewObject<UEngine>(nullptr);
	GEngine = Engine.get();
	
	// GameInstance를 생성. World 생성
	Engine->Init();

	// World에 GameMode를 지정
	// [SERVER] World->Listen();
	Engine->Start();

	UClass* Test = UEngine::StaticClass();
	return 0;
}

void FEngineLoop::Tick()
{
	//RequestEngineExit("Test");
	Engine->Tick(0.);
}

void FEngineLoop::Exit()
{
	Engine->PreExit();
	Engine = nullptr;
	GEngine = nullptr;

	for (auto& It : MapClass)
	{
		It.second->~UClass();
		GUObjectArray.Free(typeid(UClass), It.second);
	}
	MapClass.clear();

	FConfigCacheIni::DestroyConfigSystem();
}
