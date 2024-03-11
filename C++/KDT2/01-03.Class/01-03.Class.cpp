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

		//주조전달
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
}