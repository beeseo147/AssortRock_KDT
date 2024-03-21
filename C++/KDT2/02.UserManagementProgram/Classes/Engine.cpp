#include "Engine.h"
#include "Task/Task.h"
#include "MISC/Utils.h"
void FEngine::Run()
{
	Init();
	while (!bTerminated) 
	{
		system("pause");
		const EMenuEvent Event = PrintMenu();
		switch (Event)
		{
		case ETerminate:
			bTerminated = true;
			break;
		case ECreateAccount:
		{
			FCreateAccountTask Task;
			break;
		}
		case EDeleteAccount:
		{
			FDeleteAccountTask Task;
			break;
		}
		}
		
	}
	Release();
}

void FEngine::Init()
{
	cout << "[System]Start" << __FUNCTION__ << endl;
}

void FEngine::Release()
{
	cout << "[System]ShutDown" << __FUNCTION__ << endl;
}

EMenuEvent FEngine::PrintMenu()
{
	system("cls");
	cout << "[=====================================]\n";
	cout << "[=====================================]\n";
	cout << "[ Please	Input	event	number ]\n";
	cout << "[ 0) 프로그램 종료				]\n";
	cout << "[ 1) 회원 가입					]\n";
	cout << "[ 2) 회원 탈퇴					]\n";
	cout << "[=====================================]\n";
	cout << "====> \n";

	int Event = 0;
	cin >> Event;

	return static_cast<EMenuEvent>(Event);
}
