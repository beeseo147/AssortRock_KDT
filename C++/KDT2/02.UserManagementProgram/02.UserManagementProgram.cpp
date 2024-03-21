// 02.UserManagementProgram.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "MISC/Headers.h"
#include "Classes/Account.h"
#include "Classes/DataBase.h"
#include "Classes/Engine.h"
// C++을 사용해서 간단한 
// - [o]회원가입, 회원 탈퇴
// - [o]로그인, 로그아웃
// - [o]접속중인 유저 표시
// - [o]입력 인터페이스

// 회원 정보 관리
// - class FDataBase
// 계정 정보
// - struct FAccount

int main()
{
	GEngine.Run();
	

	/*FAccount Account("Hello", "World");

	FAccount* NewAccount = GDataBase.CreateAccount(Account);
	GDataBase.DeleteAccount(*NewAccount);
	GDataBase.DeleteAccount(Account);
	FAccount* NewAccount2 = GDataBase.CreateAccount(Account);*/
}