// 01-05.Template.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Template.h"
#include "Test.h"

// Class(struct)를 통해서 OOP(객체지향 프로그래밍)를 학습했습니다.
// OOP 뿐만 아니라 C++는 제네릭(generic) 프로그래밍도 지원 합니다.
// 제네릭 프로그래밍의 목적은 타입에 대해서 재사용 가능한 코드를 작성 하는 것이다.

// 절차적 프로그래밍 패러다임은 주로 함수(Function) 단위로 프로그램을 작성

// 객체지향 프로그래밍 패러다임은 객체(Object, 문법적으로 class struct)란 개념을 도입

// 제네릭 프로그래밍 패러다임은 매개변수 타입을 고정하고 값을 받는 기존 방식에서 나아가,
// 매개변수 타입에 대해서도 매개변수화(설정 가능하게_할 수 있게 만든 문법을 기반으로 하는 패러다임
// 이를 C++에서는 template이라고 합니다.

int main()
{
	{
		int Result = Sum(10, 20);
		double Result2 = Sum(10.5, 20.3);
	}
	{
		int Result22 = Hello2();
		int Result = TemplateSum<int>(10, 20);
		int Result33 = TemplateSum<int>(20, 30);
		double Result2 = TemplateSum<double>(10.5, 20.3);
		float Result3 = TemplateSum<float>(10.5, 20.3);
	}
	{
		// TAD(Template Argument Deduction; 템플릿 인수 추론)
		int Result = TemplateSum(10, 20);
		double Result2 = TemplateSum(10.5, 20.3);
	}
	{
		double Tesult = TemplateSum2<float, int>(10.5f, 4);
	}
	{
		int a = Sum2(10/*, 30*/);
	}
	{
		FClass<int, 1280> Class;
		Class.Function(1000);
		auto Result = Class.Function2<float>();
		auto Result2 = Class.Function2<int>();
		//float Result2 = Class.Function2();
	}
	{
		FClass2<int, 999, 444> Class;
		size_t Width = Class.GetWidth();
		size_t Height = Class.GetHeight();
	}
	{
		FClass3 Class;
		size_t Width = Class.GetWidth();
		size_t Height = Class.GetHeight();
	}
	{
		FClass4<444, 333> Class;
		size_t Width = Class.GetWidth();
		size_t Height = Class.GetHeight();
	}
	{
		struct FStruct
		{
			int Value = 0;
			int Value2 = 2;
		};
		FClass<FStruct, 1280> Class;
	}
	{
		FStruct A;
		FStruct B;

		FStruct Result = TemplateSum<FStruct>(A, B);
	}
	{
		ProcessValue(1, 2, 3.14f, "Hello");
	}

	// 루프 언롤링: 컴파일 시간에 반복문을 일렬로 펼쳐놓은 방식으로 처리하는 기법
	// 해당 기능을 사용하지 않아도, 컴파일러가 알아서 판단해서 언롤링이 유리하다고
	// 생각되면 기존 for문도 언롤링 해서 처리해 줍니다. (최적화가 켜져 있는 경우)
	// 굳이 아래처럼 언롤링 하지 않아도 되지만 이런것도 있구나 정도로 이해하시면 되겠습니다.
	{
		//int a = 0;
		///*for (int i = 0; i < 5; ++i)
		//{
		//	a += i;
		//}*/
		//a += 0;
		//a += 1;
		//a += 2;
		//a += 3;
		//a += 4;

		TLoop<4>::Run([](int i)
			{
				std::cout << "i: " << i << std::endl;
			});
	}
}