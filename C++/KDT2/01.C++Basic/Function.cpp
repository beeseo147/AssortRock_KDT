#include "Function.h"
#include <format>

void FunctionName()
{
}

void FunctionName(int a)
{
	//std::cout << "a: " << a << std::endl;
	std::cout << std::format("a: {}\n", a);
}

int AddFunction(int a, int b)
{
	const int Sum = a + b;
	std::cout << std::format("[{}:{}:{}] {} + {} = {}\n", __func__, __FILE__, __LINE__, a, b, Sum);
	return Sum;
}

double AddFunction(double a, double b)
{
	const double Sum = a + b;
	std::cout << std::format("[{}:{}:{}] {} + {} = {}\n", __func__, __FILE__, __LINE__, a, b, Sum);
	return Sum;
}

unsigned long long Factorial(unsigned char f)
{
	if (f == 0)
	{
		return 1;
	}
	else
	{
		return f * Factorial(f - 1);
	}
}
