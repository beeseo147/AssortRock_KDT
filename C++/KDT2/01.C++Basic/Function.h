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