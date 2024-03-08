#include "Function.h"
#include <iostream>
void AllocateWrong(int* InTarget1, int* InTarget2)
{
	InTarget1 = new int;
	InTarget2 = new int;
}

void AllocateCorrect(int** InTarget1, int** InTarget2)
{
	*InTarget1 = new int;
	*InTarget2 = new int;
}

void Delete(int* InTarget)
{
	delete InTarget;
}

void InitArray(int* const InArray, const size_t InSize)
{
	for (int i = 0; i < InSize; i++) {
		InArray[i] = i;
	}
}

void InitArray(std::vector<int>& InArray)
{
	const size_t Size = InArray.size();
	for (size_t i = 0; i < Size; ++i)
		// size함수를 한번만 호출하도록 위에 별도의 변수를
		// 만들어 두고 한번 호출했다.
		// for 조건 판단 내부에 size함수를 넣어두면
		// 원소의 갯수만큼 size함수를 호출하기 때문
	//for (size_t i = 0; i < InArray.size(); ++i)
	{
		InArray[i] = i;
	}
}

void InitArray(std::vector<int>* const InArray)
{
	const size_t Size = InArray->size();
	for (size_t i = 0; i < Size; ++i)
	{
		// 둘다 동일한 결과!
		InArray->at(i) = (int)i;
		(*InArray)[i] = (int)i;
	}
}

void Sum(const std::vector<int>& InVector, int* const OutResult)
{
	const size_t Size = InVector.size();
	int total = 0;

	/*for (size_t i = 0; i < Size; i++) {
		total += InVector[i];
	}*/
	for (int a : InVector) {
		total += a;
	}

	*OutResult = total;
}
void Swap(int& InOutFirst, int& InOutSecond)
{
	const int Temp = InOutFirst;
	InOutFirst = InOutSecond;
	InOutSecond = Temp;
}

void CustomDeleterInt(int* Inpointer)
{
	delete Inpointer;
}

void UniqueParam(std::unique_ptr<FStruct>& InPointer)
{
	InPointer->Hello();
}

void UniqueParam(std::unique_ptr<FStruct>* InPointer)
{
	(*InPointer)->Hello();

}
void UniqueParam(FStruct* InPointer)
{
	InPointer->Hello();
	(*InPointer).Hello();
}

void SharedParam(std::shared_ptr<FStruct> InPointer)
{
	InPointer->Hello();
	int Count = InPointer.use_count();
}

bool ReturnTrue()
{
	return true;
}

bool ReturnFalse()
{
	return false;
}

void Test()
{
	std::cout << "Test\n";
}

int SumFunction(const int a, const int b)
{
	return a+b;
}

void FunctionFunction(std::function<void()> InFunction)
{
	std::cout << __FUNCTION__ << std::endl;
	InFunction();
}


void FStruct::Hello()
{
	std::cout << "굿\n";
	std::cout << Value;
}
FStruct::FStruct(int InA)
	:Value(InA)
{

}

FStruct::FStruct(float InA)
	:Value(InA)
{
}
