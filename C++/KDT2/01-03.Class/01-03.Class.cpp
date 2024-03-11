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
		FClass ClassInstnace__ = FClass();
		FClass ClassInstnace___ = FClass();
		FClass ClassInstnace2 = FClass(TEXT("Text"));
		FClass ClassInstance3 = FClass(ClassInstnace2);

		int a = 0, b = 10;
		a = b = 30;

		ClassInstance3 = (ClassInstnace = ClassInstnace2);
		ClassInstance3.operator=(ClassInstnace.operator=(ClassInstnace2));

		ClassInstance3 = 30;

		FClass* Class = new FClass;
		FClass* Class2 = new FClass;

		//주소전달
		//Class = Class2;

		*Class = *Class2;
		delete Class;
		delete Class2;
	}
	//STATIC
	{
		FClass ClassInstnace = FClass();
		FClass ClassInstnace__ = FClass();
		FClass ClassInstnace___ = FClass();

		FClass::StaticStructClassMember.Value = 200;
		FClass::Test();
		ClassInstnace__.Test();

	
	}
	{
		FClass* Class = nullptr;
		//Hello 함수에서 this포인터 접근하는 코드가없기때문에
		//문제가 발생하지않는다.
		Class->Hello();
	}
	//Friend : 내가 대상을 친구로 생각하면
	//내 private(protected)에 접근할 수 있다.
	{
		class FClassA
		{
			friend class FManagerClass;
		private:
			FClassA()
			{

			}
			void SetValue(const int InValue) {
				ClassAPrivateDataButCanAccessFromFirend = InValue;
			}
			int ClassAPrivateDataButCanAccessFromFirend = 10;
		};

		// 싱글턴(singletone)
		class FManagerClass
		{
		public:
			static FManagerClass* Get()
			{
				static std::unique_ptr<FManagerClass> Instance{ new FManagerClass }; //= std::make_unique<FManagerClass>();
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
	//이동 의미론(move semantics)
	{
		//InValue(left value; 좌측값) 이름이 있는 변수(이름으로 주소를 얻을 수 있다)
		//RValue(right value; 우측값) InValue가 아닌 나머지 리터럴(상수)임시객체
		int a = 5 + 10;//a는 InValue 이름(a)을 가지고 있으며 &a를 통해 주소를 가져올 수 있다
		//반면 5+10이라는 표현식은 RValue이다
		//임시값이라서 해당 문장을 실행하고 나면 제거된다
		//임시값의 복사본을 a라는 변수에 저장한다.


		const char* Hello = "Hello";
		std::string Message = std::string(Hello);
							//InValue reference
		auto Function = [](std::string& InString) {
			InString;
			};

							//RValue reference
		auto Function2 = [](std::string&& InString) {
			InString[0] = 'A';
			};

		Function(Message);
		Function2("WoW");

		std::string Message2 = "World!";
		Function2(Message+ Message2);
		
	}

	{
		FClass Class = FClass();
		FClass ClassCopy = Class;

		//std::move : Invalue를 rvalue로 cast한다
		//이동생성자가 구현되어 있지않다면 복사 생성자가 호출된다.

		FClass ClassMove = FClass(std::move(Class));
	}
	{
		std::vector<int>Vector;
		Vector.resize(100000);
		Vector[0] = 100;
		Vector[1] = 2200;

		std::vector<int> Vector2 = Vector;
		Vector[0] = 200;
		Vector2[0] = 999;

		std::vector<int> Vector3 = std::move(Vector);
		//Vector[0] = 999;
		Vector3[2] = 1234;

	}
	{
		std::vector<FClass> Vector;
		Vector.resize(10);

		std::vector<FClass> Vecotr2 = Vector;
		std::vector<FClass> Vector3 = std::move(Vector);
	}
	{
		std::vector<FClass> Vector;
		Vector.reserve(10);
		Vector.emplace_back();
		Vector.emplace_back();
		Vector.emplace_back();
	}
}