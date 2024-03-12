// 01-03.Class.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Class.h"

int main()
{
	{
		// FClass라는 설계도를 기반으로
		// 실체화된 사례(instance)를 만든다
		// An Object is an instance of a class (객체는 클래스의 인스턴스입니다)
		FClass ClassInstnace = FClass();
		FClass ClassInstnace2 = FClass(TEXT("Text"));
		FClass ClassInstance3 = FClass(ClassInstnace2);

		int a = 0, b = 10;
		a = b = 30;

		ClassInstance3 = (ClassInstnace = ClassInstnace2);
		ClassInstance3.operator=(ClassInstnace.operator=(ClassInstnace2));

		ClassInstance3 = 30;

		FClass* Class = new FClass;
		FClass* Class2 = new FClass;

		// 주소 전달
		//Class = Class2;

		*Class = *Class2;
		//Class->operator=(*Class2);

		delete Class;
		delete Class2;
	}

	// static
	{
		FClass::StaticStructInClassMember.Value = 100;
		FClass ClassInstnace_ = FClass();
		FClass ClassInstnace__ = FClass();
		FClass ClassInstnace___ = FClass();

		FClass::StaticStructInClassMember.Value = 200;
		FClass::Test();
		ClassInstnace___.Test();

		FUtils::Func();
	}
	{
		FClass* Class = nullptr;
		// Hello 함수 내부에서 this에 접근하는 코드가 없어서
		// 문제가 발생하지 않는다.
		Class->Hello();
		Class->Test();
	}

	// Friend: 내가 대상을 친구로 생각하면
	// 내 private(protected)에 접근할 수 있어
	{
		class FClassA
		{
			friend class FManagerClass;
		private:
			FClassA()
			{

			}

			void SetValue(const int InValue)
			{
				ClassAPrivateDataButCanAaccessFromFriend = InValue;
			}

		private:
			int ClassAPrivateDataButCanAaccessFromFriend = 10;
		};

		// 생성자가 private이라 instance를 만들 수 없다!
		/*FClassA Class;
		Class.SetValue(100);*/

		// 싱글턴(singleton) 패턴: instance가 하나만 있다
		// UE: Subsystem
		class FManagerClass
		{
		public:
			static FManagerClass* Get()
			{
				static std::unique_ptr<FManagerClass> Instance{ new FManagerClass };
				return Instance.get();
			}

			~FManagerClass()
			{
			}

			void SetValue(const int InValue)
			{
				Class.SetValue(InValue);
			}

		private:
			FManagerClass()
			{

			}

		private:
			FClassA Class;
		};

		FManagerClass* Instance = FManagerClass::Get();
		Instance->SetValue(1000);
		Instance->SetValue(200);
		Instance->SetValue(500);

		FManagerClass::Get()->SetValue(100);
		FManagerClass::Get()->SetValue(200);
		FManagerClass::Get()->SetValue(300);
		//FManagerClass Test;	// 생성자가 private이라 instance를 만들 수 없다!
	}

	// 이동 의미론(move semantics)
	{
		// lvalue(left value; 좌측값): 이름이 있는 변수(이름으로 주소를 얻어올 수 있다)
		// rvalue(right vlaue; 우측값): lvalue가 아닌 나머지, 리터럴(상수), 임시 객체
		int a = 5 + 10;	// a는 lvalue이며, 이름(a)을 갖고 있으며, &a로 주소를 가져올 수 있다
		// 반면, 5+10 이라는 표현식은 rvalue다.
		// rvalue는 임싯값이라서 해당 문장을 실행하고 나면 제거된다.
		// 임싯값의 복사본을 a라는 변수에 저장하고 있습니다.

		//			lvalue   rvalue
		const char* Hello = "Hello";
		std::string Message = std::string(Hello); // 둘다 lvalue

		// lvalue reference
		auto Function = [](std::string& InString)
			{
				InString;
			};


		std::string* StringPointer = nullptr;
		// rvalue reference
		auto Function2 = [&StringPointer](std::string&& InString)
			{
				InString[0] = 'A';
				StringPointer = &InString;
			};
		Function(Message);
		Function2("Wow");

		std::string Message2 = "World!";
		Function2(Message + Message2);

		// rvalue가 지정된 함수를 벗어나는 순간 소멸자가 호출됨.
		// 아래처럼 사용하면 동작을 보장할 수 없다
		/*struct FTest
		{
			~FTest()
			{
				std::cout << "Test\n";
				Value = 1;
			}

			int Value = 10;
		};
		FTest* Test = nullptr;
		auto Function3 = [&Test](FTest&& InString)
			{
				Test = &InString;
			};

		Function3(FTest());

		int abb = 0;*/
	}

	{
		FClass Class = FClass(TEXT("Wowowowow"));
		//FClass ClassCopy = FClass(Class);
		FClass ClassCopy = Class;

		// std::move : lvalue를 rvalue로 cast 한다
		// 이동생성자가 구현되어 있지 않다면 복사 생성자가 호출됩니다.
		FClass ClassMove = FClass(std::move(Class));
	}
	{
		std::vector<int> Vector;
		Vector.resize(10000);
		Vector[0] = 100;
		Vector[1] = 2200;

		std::vector<int> Vector2 = Vector;
		Vector[0] = 1000;
		Vector2[0] = 999;

		std::vector<int> Vector3 = std::move(Vector);
		Vector3[2] = 1234;
	}
	{
		std::vector<FClass> Vector;
		Vector.resize(10);		// 공간 할당과 동시에 값을 초기화 한다

		std::vector<FClass> Vector2 = Vector;
		std::vector<FClass> Vector3 = std::move(Vector);
	}
	{
		std::vector<FClass> Vector;
		Vector.reserve(10);		// 미리 공간만 할당 한다
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();

		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();

		Vector.emplace_back();
		size_t S = Vector.size();
		size_t C = Vector.capacity();
	}
}
