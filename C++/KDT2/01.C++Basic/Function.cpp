#include "Function.h"
#include <iostream>
#include <format>

void FunctionName()
{
}

void FunctionName(int a)
{
	//std::cout << "a: " << a << std::endl;
	std::cout << std::format("a: {}\n", a);
}
