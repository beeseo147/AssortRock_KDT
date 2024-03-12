#pragma once
#include <iostream>

// class 이름 앞에 I(i)를 붙혀서
// interface라고 티를 내주는 편이 많다
class IInterface
{
	// 인터페이스를 사용하는 목적은
	// 반드시 다음과 같은 함수가 존재한다
public:
	virtual void MustFunction() = 0;	// =0; 순수 가상 함수
	// 순수가상함수: 함수의 선언만 있고 구현은 이를 상속받는
	// class에서 반드시 구현하라

	virtual void MustFunction2()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	//public:
	//	int Value = 0;
};

inline void FunctionMustInterface(IInterface* InInterface)
{
	InInterface->MustFunction();
	InInterface->MustFunction2();
}