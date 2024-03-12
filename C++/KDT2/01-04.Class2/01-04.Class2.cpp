// 01-04.Class2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Classes/Derived.h"

int main()
{
	{
		int a = 9;
		int b = 8;
		// Stack
		// 
		// 0x0000 : int FBase::PublicValue
		// 0x0004 : int FBase::ProtectedValue
		// 0x0008 : int FBase::PrivateValue
		// 0x000C : int FBase::PrivateValue2
		// 
		// 0x0010 : int FDerived::DerivedPublicValue
		// 0x0014 : int FDerived::DerivedPublicValue2
		//
		// 1. FDerived 생성자로 진입 (실행은 x)
		// 2. FBase의 생성자로 진입
		// 3. FBase의 초기화 구문 실행(변수 초기화)
		// 4. FBase의 생성자 실행
		// 5. FDerived의 초기화 구문 실행(변수 초기화)
		// 6. FDerived의 생성자 실행 
		FDerived Derived;
		Derived.DerivedPublicValue;
		Derived.DerivedPublicValue2;
		Derived.PublicValue;
		Derived.PublicMethod();

		// Up cast: 자식을 부모로 cast 하는 경우(묵시적 cast)
		FBase* PointerBase = &Derived;
		PointerBase->PublicMethod();
		// Down Cast를 했지만 원래 Derived 타입이였기 때문에 문제가 없다
		FDerived* PointerDerived = (FDerived*)PointerBase;
		PointerDerived->PublicMethod();
	}
	{
		// 1. FBase의 생성자로 진입
		// 2. FBase의 초기화 구문 실행(변수 초기화)
		// 3. FBase의 생성자 실행
		FBase Base;
		int aa = 100;
		int bb = 200;
		Base.PublicMethod();
		// Down cast: 부모를 자식으로 cast하는 경우(명시적 cast)
		// 아주 아주 위험, 특별한 이유가 없다면 하면 안되겠죠
		FDerived* PointerDerived = (FDerived*)&Base;
		PointerDerived->PublicMethod();
		//PointerDerived->DerivedPublicValue = 999;
		//PointerDerived->DerivedPublicValue = 999;
	}
}