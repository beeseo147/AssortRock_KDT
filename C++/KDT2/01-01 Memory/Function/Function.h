#pragma once
#include<vector>

void AllocateWrong(int* InTarget1, int* InTarget2);
void AllocateCorrect(int** InTarget1, int** InTarget2);
void Delete(int* InTarget);

void InitArray(int* const InArray, const size_t InSize);
void InitArray(std::vector<int>& InArray);
void InitArray(std::vector<int>* const InArray);

void Sum(const std::vector<int>& InVector, int* const OutResult);
void Swap(int& InFirst, int& InSecond);

void CustomDeleterInt(int* InPointer);

struct FStruct
{
	FStruct() = default;
	FStruct(const FStruct& InOther) = default;
	//FStruct(const FStruct&& InOther) = default;
	FStruct& operator = (const FStruct& InOther) =default;
	~FStruct() = default;

	void Hello();
private:
	int Value;
};

void UniqueParam(std::unique_ptr<FStruct>& InPointer);
void UniqueParam(std::unique_ptr<FStruct>* InPointer);
void UniqueParam(FStruct* InPointer);