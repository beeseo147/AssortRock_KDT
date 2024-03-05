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
void HasFlag(unsigned char Inproperty) {
	// 1번 속성이 활성화 되어 있나요?
	// 0000 0001
	// 0000 0001
	// -------And (둘다 1이면 1,하나라도 0이면 0)
	// 0000 0001
	// 참
	// if는 0이면 flase , 0이 아니면 true

	if (Inproperty & EproertyFlags::Eproperty1) {
		std::cout << "EproertyFlags::Eproperty1\n";
	}
	if (Inproperty & EproertyFlags::Eproperty2) {
		std::cout << "EproertyFlags::Eproperty2\n";
	}
	if (Inproperty & EproertyFlags::Eproperty3) {
		std::cout << "EproertyFlags::Eproperty3\n";
	}
	if (Inproperty & EproertyFlags::Eproperty4) {
		std::cout << "EproertyFlags::Eproperty4\n";
	}
	if (Inproperty & EproertyFlags::Eproperty5) {
		std::cout << "EproertyFlags::Eproperty5\n";
	}
	if (Inproperty & EproertyFlags::Eproperty6) {
		std::cout << "EproertyFlags::Eproperty6\n";
	}
	if (Inproperty & EproertyFlags::Eproperty7) {
		std::cout << "EproertyFlags::Eproperty7\n";
	}
	if (Inproperty & EproertyFlags::Eproperty8) {
		std::cout << "EproertyFlags::Eproperty8\n";
	}
}

// int a = Value;
int Function(int a)
{
	a = 10;
	return a;
}

FParam Function(FParam InParam)
{
	for (int i = 0; i < 1000; ++i)
	{
		InParam.Value[i] = i;
	}
	return InParam;
}

void Function(FParam* InParam)
{
	for (int i = 0; i < 1000; ++i)
	{
		InParam->Value[i] = i;
	}
}

void FunctionCallByPointer(int* InParam)
{
	*InParam += 1;
}

void FunctionCallByReference(int& InParam)
{
	InParam += 1;
}

void FunctionCallByReference(FParam& InParam)
{
	for (int i = 0; i < 1000; ++i)
	{
		InParam.Value[i] = i;
	}
}
