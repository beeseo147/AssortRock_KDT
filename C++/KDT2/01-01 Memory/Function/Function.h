#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <format>
#include <random>
void AllocateWrong(int* InTarget1, int* InTarget2);
void AllocateCorrect(int** InTarget1, int** InTarget2);
void Delete(int* InTarget);

void InitArray(int* const InArray, const size_t InSize);
void InitArray(std::vector<int>& InArray);
void InitArray(std::vector<int>* const InArray);

void Sum(const std::vector<int>& InVector, int* const OutResult);
void Swap(int& InFirst, int& InSecond);

void CustomDeleterInt(int* InPointer);

//포인터로부터 스마트 포인터를 가져올 수 있다
struct FStruct : public std::enable_shared_from_this<FStruct>
{
	FStruct() = default;
	FStruct(int InA);
	FStruct(float InA);
	FStruct(const FStruct& InOther) = default;
	//FStruct(const FStruct&& InOther) = default;
	//void operator=(const FStruct& InOther);
	FStruct& operator=(const FStruct& InOther) = default;
	~FStruct() = default;

	void SetValue(int InValue) { Value = InValue; }
	void Hello();

private:
	int Value = 0;
};

void UniqueParam(std::unique_ptr<FStruct>& InPointer);
void UniqueParam(std::unique_ptr<FStruct>* InPointer);
void UniqueParam(FStruct* InPointer);
void SharedParam(std::shared_ptr<FStruct> InPointer);

bool ReturnTrue();
bool ReturnFalse();

void Test();
void FunctionFunction(std::function<void()> InFunction);
int SumFunction(const int a, const int b);