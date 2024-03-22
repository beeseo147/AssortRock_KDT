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
		case ETerminate://0
			bTerminated = true;
			break;
		case ECreateAccount://1
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FCreateAccountTask Task;
			break;
		}
		case EDeleteAccount://2
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FDeleteAccountTask Task;
			break;
		}
		case EPrintAccount://3
		{
			FPrintAccountTask Task;
			break;
		}
		case ELogIn:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FLoginTask Task;
			break;
		}
		case ELogout:
		{
			FPrintAccountTask PrintAccountTask;
			FPrintLoginPlayerTask PrintLoginPlayerTask;
			FLogoutTask Task;
			break;
		}
		case EPrintLoginPlayer:
		{
			FPrintLoginPlayerTask Task;
			break;
		}
		default:
			bTerminated = true;
			break;
		}
	}
	
	Release();
	//Enum 이외의 값이 들어올 경우 While문을 빠져나와 Run()함수가 종료된다.
}

void FEngine::Init()
{
	cout << format("[System]Start {}\n", __FUNCTION__);
}

void FEngine::Release()
{
	cout << format("[System]Shutdown {}\n", __FUNCTION__);
	FAllPlayerLogout Task;
}

EMenuEvent FEngine::PrintMenu()
{
	system("cls");
	cout << "[---------------------------]" << endl;
	cout << "[ Please input event number ]" << endl;
	cout << "[ 0) 프로그램 종료          ]" << endl;
	cout << "[ 1) 회원 가입              ]" << endl;
	cout << "[ 2) 회원 탈퇴              ]" << endl;
	cout << "[ 3) 회원 정보 출력         ]" << endl;
	cout << "[ 4) 로그인                 ]" << endl;
	cout << "[ 5) 로그아웃               ]" << endl;
	cout << "[ 6) 로그인 유저 정보 출력  ]" << endl;
	cout << "[---------------------------]" << endl;
	cout << "--> ";

	int Event = 0;
	cin >> Event;

	return static_cast<EMenuEvent>(Event);
}
