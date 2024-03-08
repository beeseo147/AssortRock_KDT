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

void InitVector(std::vector<int>& InArray)
{
	const size_t Size = InArray.size();
	for (size_t i = 0; i < Size; i++) {
		InArray[i] = i;
	}
}

void InitVector(std::vector<int>* InArray)
{
	const size_t Size = InArray->size();
	for (size_t i = 0; i < Size; i++) {
		InArray->at(i) = i;
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

void FStruct::Hello()
{
	std::cout << "굿\n";
}
