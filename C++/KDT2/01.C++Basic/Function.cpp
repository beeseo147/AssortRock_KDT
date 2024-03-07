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
#include <cassert>
void FunctionWithPointer(int* InPointer)
{
	//debug 모드일때 동작하는 assert는
	//프로그래머의 명백한 실수를 탐지하기 위해 사용
	
	//_ASSERT(InPointer != nullptr);
	//if (!InPointer)	return;
	if (InPointer == nullptr) {
		_ASSERT(false);
		return;
	}
		

	*InPointer += 100;
}
//In : 밖에서 값을 채워서 준다
//Out : 값이 함수 내부에서 바뀌어서 나온다.
void Swap(int& InOutFirst, int& InOutSecond)
{
	//Temp = A(10)
	const int Temp = InOutFirst;

	InOutFirst = InOutSecond;
	InOutSecond = Temp;
}

void Swap(int* InOutFirst, int* InOutSecond)
{
	//Temp = A(10)
	const int Temp = *InOutFirst;

	*InOutFirst = *InOutSecond;
	*InOutSecond = Temp;
}

void SeperateOddsAndEvens(const std::array<int, 10>* InNumbers, std::vector<int>* OutOdds, std::vector<int>* OutEvens)
{
	for (int Value : *InNumbers) {
		if (Value % 2 == 0) {
			OutEvens->push_back(Value);
		}
		else
		{
			OutOdds->push_back(Value);
		}
	}
}

void SeperateOddsAndEvens(const std::array<int, 10>& InNumbers, std::vector<int>& OutOdds, std::vector<int>& OutEvens)
{
	for (int Value : InNumbers) {
		if (Value % 2 == 0) {
			OutEvens.push_back(Value);
		}
		else
		{
			OutOdds.push_back(Value);
		}
	}
}
FOddsAndEvens SeperateOddsAndEvens(const std::array<int, 10>& InNumbers)
{
	std::vector<int> Odds, Evens;
	for (int Value : InNumbers) {
		if (Value % 2 == 0) {
			Evens.push_back(Value);
		}
		else
		{
			Odds.push_back(Value);
		}
	}
	//
	return FOddsAndEvens(Odds, Evens);
}
void Test(int aa) {
	aa = 100;
}

void TestReference(int &aa)
{
	aa = 100;
}

void TestPointer(int* aa)
{
	*aa = 100;
}

int sum(std::initializer_list<int> InValues)
{
	int Total = {};
	for (int i : InValues) {
		Total += i;
	}
	return Total;
}

int sum2(std::vector<int> InValues)
{
	int Total = {};
	for (int i : InValues) {
		Total += i;
	}
	return Total;
}
