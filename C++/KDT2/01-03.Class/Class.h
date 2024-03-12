#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

// Class, Struct
//{
//	// Members...
//		// - 접근 지정자(Access modifier)
//			// - public: 어디서든 접근 가능
//			// - private: 해당 class, struct 내부에서 접근 가능
//		// - 맴버 변수(Variable)
//			// - enum, 중첩class struct, type alias(using)
//			// - 변수들(int ,float, ... custom type(class, struct))
//			// - static(정적) 변수
//			// - ...
//		// - 맴버 함수(Function)
//			// - Method(member function)
//			// - Constructor(생성자)
//			// - Destructor(소멸자)
//			// - 연산자(operator =,-,+, ...)
//			// - static(정적) 함수
//}

struct FStruct
{
	// 기본 접근 지정자: public
	FStruct()
		: Value(100)	// 초기화(생성자에 위치한 초기화 구문의 우선
		// 순위가 더 높다)
		// 이 생성자로 Value를 초기화하면 100
	{

	}
	~FStruct()
	{

	}

	//private:
	int Value = 0;	// 초기화
};

class FClass
{
	// 기본 접근 지정자: private
public:
	// 프로그램이 켜질 때 해당 인스턴스가 만들어집니다.
	// 꺼질때 삭제됩니다.
	// static 변수에 inline키워드를 붙히면
	// h에 선언만 해도 인스턴스를 만들어 줍니다.
	// 하지만 dll에서 이걸 사용할떄 아주 주의해서 사용해야 합니다.
	inline static FStruct StaticStructInClassMember;

	// static 함수를 만들수 있다!
	// this pointer가 파라미터로 들어오지 않는 함수
	// 일반 함수와 동일
	static void Test()
	{
		std::cout << "Test\n";
		/*Value;
		this;*/
	}

	// __thiscall의 특성을 생각하시면
	// this pointer에 접근하지 않으면 문제가 없어야 한다
	void Hello()
	{
		std::cout << "Hello\n";
		//*Pointer = 10999;
	}

public:
	FClass()
		: Value(100)
		, Pointer(new int(Value))
	{
		// 함수 내부에 있는 static 변수의 경우
		// 해당 함수의 해당 위치에 처음 왔을때 인스턴스가 만들어지며
		// 이후에는 만들어지지 않고, 해당 메모리에 계속 접근은 할수 있다
		// 프로그램이 종료될때 소멸한다
		static FStruct StructInstance;
		++StructInstance.Value;
		std::cout << StructInstance.Value << std::endl;
	}

	FClass(const std::wstring_view InString)
		: Pointer{ new int(Value) }
		, String(InString)
	{
		std::wcout << String << std::endl;
	}

	// 복사 생성자(선언하지 않더라도 기본적으로 만들어줌)
	// 기본 복사생성자로 복사하는 경우 이를 얕은 복사
	// 아래처럼 추가로 동적할당에 대한 처리를 하는 경우 깊은 복사
	FClass(const FClass& InOther)
		: Value(InOther.Value)
		, Pointer(new int{ Value })
		, String(InOther.String)
	{
		std::wcout << String << std::endl;
	}

	// 이동 생성자
	FClass(FClass&& InOther) noexcept
		// string에 구현되어 있는 이동 생성자에 의해서
		// this->String이 생성됩니다.

		// string은 특정 상황을 만족했을때 데이터를 stack 보관
		// 이 상황일 경우 복사가 move를 한다고 하더라도 발생
		// 이 경우에는 move가 의미가 없다
		// 하지만 문자열이 긴 경우 Heap에 할당되는데
		// 이럴때는 주소만 변경하면 되기 때문에 빠르다
		: Value(InOther.Value)
		, Pointer(InOther.Pointer)
		, String(std::move(InOther.String))
	{
		InOther.Value = 0;
		InOther.Pointer = nullptr;
	}

	~FClass()
	{
		if (Pointer)
		{
			delete Pointer;
			Pointer = nullptr;
		}
	}

	// 대입 연산자 오버로딩(선언하지 않더라도 기본적으로 만들어줌)
	// 기본 대입 연산자로 복사하는 경우 이를 얕은 복사
	// 아래처럼 추가로 포인터 값복사 처리를 하는 경우 깊은 복사
	//void operator=(const FClass& InOther)
	FClass& operator=(const FClass& InOther)
		//FClass* operator=(const FClass& InOther)
	{
		Value = InOther.Value;
		*Pointer = *InOther.Pointer;
		String = InOther.String;

		return *this;
	}

	FClass& operator=(const int InOther)
	{
		Value = InOther;
		return *this;
	}

private:
	int Value = 0;
	int* Pointer = nullptr;
	std::wstring String;
};

class FUtils
{
public:
	static void Func() {}
};