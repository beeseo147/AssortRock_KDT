// #pragma once: 한번만 이 파일이 포함되게 해주세요
#pragma once
#include <iostream>

void /*__cdecl*/ FunctionName();
// 이름이 같고, 파라미터가 다른 함수를
// 함수를 오버로딩 했다고 표현합니다.
void FunctionName(int a);

[[nodiscard("할말")]] int AddFunction(int a, int b);
[[nodiscard("할말")]] double AddFunction(double a, double b);

inline bool First()
{
	std::cout << "[First]\n";
	return true;
}

inline bool Second()
{
	std::cout << "[Second]\n";
	return false;
}

// 재귀함수: 그 함수가 자기 자신을 호출하는 함수
[[nodiscard("")]] unsigned long long Factorial(unsigned char f);

enum EproertyFlags : unsigned char
{

	ENone			 = 0x00 , //0000 0000
	Eproperty1		= 0x01,
	Eproperty2		= 0x02,
	Eproperty3		= 0x04,
	Eproperty4		= 0x08,
	Eproperty5		= 0x10,
	Eproperty6		= 0x20,
	Eproperty7		= 0x40,
	Eproperty8		= 0x80,

};

void HasFlag(unsigned char Inproperty);

struct FParam
{
	FParam()
	{
		std::cout << "FPram\n";
	}

	FParam(int a)
	{
		std::cout << "FPram int a\n";
		Value[0] = a;
	}

	// 복사 생성자: 선언하지 않으면 자동으로 만들어 줍니다.
	// InParam 데이터를 기반으로 나(인스턴스)를 만드는데 그 데이터를
	// 가지고 와서 채울 목적으로 보통 사용하기 위해 복사생성자를 
	// 만듭니다.

	// 원본을 수정하지 않을 목적으로 const를 붙힘
	// 선언하지 않으면 자동으로 만들어주는 복사 생성자 같은 경우
	// 자동으로 InParam에 있는 모든 데이터를 복사해온다

	// 생성자류는 새로운 인스턴스가 만들어질때만 호출됩니다. (초기화 되는 시점)
	FParam(const FParam& InParam)
	{
		std::cout << "FPram 복사 생성자\n";
		for (int i = 0; i < 1000; ++i)
		{
			this->Value[i] = InParam.Value[i];
		}
	}

	// 대입 연산자
	// 예도 자동으로 만들어줌: 복사생성자랑 비슷하게 값을 복제
	// 연산자 오버로딩
	FParam& operator = (const FParam& InParam)
	{
		std::cout << "FPram 대입 연산자\n";
		for (int i = 0; i < 1000; ++i)
		{
			this->Value[i] = InParam.Value[i];
		}
		return *this;
	}

	~FParam()
	{
		std::cout << "~FPram\n";
	}

	int Value[1000]{};
};

// CallByValue
int Function(int a);
FParam Function(FParam InParam);
// CallByPointer
void Function(FParam* InParam);

void FunctionCallByPointer(int* InParam);
// CallByReference
void FunctionCallByReference(int& InParam);
void FunctionCallByReference(FParam& InParam);