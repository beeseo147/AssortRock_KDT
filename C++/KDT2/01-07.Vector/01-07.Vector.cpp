// 01-07.Vector.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include "Containers/Vector.h"

using std::cout;
using std::endl;

struct FStruct
{
	size_t Value = 0;
	size_t* Pointer = new size_t(Value);

	FStruct() = default;
	FStruct(const size_t InValue)
		: Value(InValue)
		, Pointer(new size_t(Value)) {}
	FStruct(const FStruct& InStruct)
		: Value(InStruct.Value)
		, Pointer(new size_t(Value)) {}
	FStruct(FStruct&& InStruct) noexcept
		: Value(InStruct.Value)
		, Pointer(InStruct.Pointer)
	{
		InStruct.Value = 0;
		InStruct.Pointer = nullptr;
	}
	~FStruct()
	{
		if (Pointer)
		{
			delete Pointer;
			Pointer = nullptr;
		}
	}
};

int main()
{
	int Value = KDT::Test();
	{
		cout << "KDT::vector" << endl;
		KDT::vector<int> Vector;
		for (int i = 0; i < 10; ++i)
		{
			cout << i << endl;
			Vector.push_back(i);
		}

		KDT::vector<FStruct> Vector2;
		//Vector2.reserve(10);
		for (int i = 0; i < 10; ++i)
		{
			Vector2.push_back(FStruct(i));
		}
		Vector2.resize(11);
		Vector2.clear();
		for (int i = 0; i < 5; ++i)
		{
			Vector2.push_back(FStruct(i));
		}

		size_t Size = Vector2.size();
		size_t Cap = Vector2.capacity();

		FStruct& Data = Vector2[0];
		Data.Value = 89;
		FStruct& Data2 = Vector2[1];
		Data2.Value = 999;
	}
	{
		/*std::vector<FTest> Vector2;
		Vector2.reserve(10);
		for (int i = 0; i < 10; ++i)
		{
			Vector2.push_back(FTest(i));
		}*/
		cout << "std::vector" << endl;
		std::vector<int> Vector;
		Vector.reserve(10);
		for (int i = 0; i < 10; ++i)
		{
			cout << i << endl;
			Vector.push_back(i);
		}

		for (int i : Vector)
		{
			cout << i << endl;
		}

		std::vector<int>::iterator ItEnd = Vector.end();
		for (std::vector<int>::iterator It = Vector.begin(); It != ItEnd; ++It)
		{
			cout << *It << endl;
		}

		std::vector<int>::iterator It = Vector.begin();
		++It;
		++It;
		--It;
	}
}