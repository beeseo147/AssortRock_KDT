// 01-07.Vector.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <format>
#include <map>
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

		auto ItInt = Vector.begin();
		int Val = *ItInt;

		KDT::vector<FStruct> Vector2;
		//Vector2.reserve(10);
		for (int i = 0; i < 10; ++i)
		{
			Vector2.push_back(FStruct(i));
			//FStruct Test = FStruct(i);
			//Vector2.push_back(Test);
		}
		Vector2.resize(2);
		Vector2.resize(1);
		Vector2.resize(2);
		Vector2.clear();
		for (int i = 0; i < 5; ++i)
		{
			Vector2.push_back(FStruct(i));
		}

		size_t Size = Vector2.size();
		size_t Cap = Vector2.capacity();

		FStruct& Data = Vector2[0];
		KDT::vector<FStruct>::iterator It = Vector2.begin();
		KDT::vector<FStruct>::iterator It2 = ++It;
		KDT::vector<FStruct>::iterator It3 = It++;
		++It;
		--It;
		(*It).Value;
		It->Value;
		//It3 = It;
		KDT::vector<FStruct>::iterator It4 = It;
		KDT::vector<FStruct>::iterator ItEnd = Vector2.end();

		for (FStruct& Value : Vector2)
		{
			cout << std::format("Value: {}\n", Value.Value);
		}

		Data.Value = 89;
		FStruct& Data2 = Vector2[1];
		//FStruct& Data3 = Vector2["2"];
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

	// vector 사용시 주의점
	{
		std::vector<int> Vector;
		Vector.push_back(10);
		// 뎅글링 포인터
		std::vector<int>::iterator It = Vector.begin();
		int& Value = Vector.back();

		// 재할당으로 인해 기존에 가리키던 주소가 무효화됨
		// Value, It가 의미없는 주소를 가리킴
		Vector.push_back(20);
		std::vector<int>::iterator It2 = Vector.begin();
		Vector.erase(Vector.begin());
		/*for (int i = 0; i < 10; ++i)
		{
			if (...)
			{
				Vector.erase(Vector.begin() + i);
			}
		}*/
	}
	{
		KDT::vector<int> Vector;
		Vector.push_back(10);
		// 뎅글링 포인터
		KDT::vector<int>::iterator It = Vector.begin();
		int& Value = Vector[0];
		Vector.push_back(20);

		// 우리 vector는 초기 size가 2로 잡혀서 2개 추가하면 그렇게됨
		// 재할당으로 인해 기존에 가리키던 주소가 무효화됨
		// Value, It가 의미없는 주소를 가리킴
		Vector.push_back(30);
	}
	{
		std::map<int, int> Map;
		std::pair<std::map<int, int>::iterator, bool> It = Map.insert(std::make_pair(0, 100));
		It.second; // insert 성공 유무
		It.first->first;	// key int
		It.first->second;	// value int
		std::pair<std::map<int, int>::iterator, bool> It2 = Map.insert(std::make_pair(1, 100));

		for (int i = 0; i < 10000; ++i)
		{
			Map.insert(std::make_pair(i, 100));
		}
	}
}