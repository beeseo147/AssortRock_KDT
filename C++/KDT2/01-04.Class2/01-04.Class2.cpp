// 01-04.Class2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Classes/NonVirtual/Derived.h"
#include "Classes/Virtual/DerivedVirtual.h"

void Function(FBaseVirtual* InBV)
{
	InBV->PublicMethod();
}
//void Function(FDerivedVirtual* InBV)
//{
//	InBV->PublicMethod();
//}
int main()
{
	{
		int a = 9;
		int b = 8;
		// Stack
		// 
		// 0x0000 : int FBase::PublicValue
		// 0x0004 : int FBase::ProtectedValue
		// 0x0008 : int FBase::PrivateValue
		// 0x000C : int FBase::PrivateValue2
		// 
		// 0x0010 : int FDerived::DerivedPublicValue
		// 0x0014 : int FDerived::DerivedPublicValue2
		//
		// 1. FDerived 생성자로 진입 (실행은 x)
		// 2. FBase의 생성자로 진입
		// 3. FBase의 초기화 구문 실행(변수 초기화)
		// 4. FBase의 생성자 실행
		// 5. FDerived의 초기화 구문 실행(변수 초기화)
		// 6. FDerived의 생성자 실행 
		FDerived Derived;
		Derived.DerivedPublicValue;
		Derived.DerivedPublicValue2;
		Derived.PublicValue;
		Derived.PublicMethod();

		// Up cast: 자식을 부모로 cast 하는 경우(묵시적 cast)
		FBase* PointerBase = &Derived;
		PointerBase->PublicMethod();
		// Down Cast를 했지만 원래 Derived 타입이였기 때문에 문제가 없다
		FDerived* PointerDerived = (FDerived*)PointerBase;
		PointerDerived->PublicMethod();

		//~FDerived() 소멸자 호출
		//~FBase() 소멸자 호출
	}
	{
		// 1. FBase의 생성자로 진입
		// 2. FBase의 초기화 구문 실행(변수 초기화)
		// 3. FBase의 생성자 실행
		FBase Base;				// 0x0000 : int FBase::PublicValue
		// 0x0004 : int FBase::ProtectedValue
		// 0x0008 : int FBase::PrivateValue
		// 0x000C : int FBase::PrivateValue2		

		int aa = 100;			// 0x0010 : int FDerived::DerivedPublicValue    <----
		int bb = 200;			// 0x0014 : int FDerived::DerivedPublicValue2	    ｜
		//		｜
		Base.PublicMethod();												//		｜
		//																	//		｜
		// Down cast: 부모를 자식으로 cast하는 경우(명시적 cast)			//		｜
		// 아주 아주 위험, 특별한 이유가 없다면 하면 안된다.				//		｜
		FDerived* PointerDerived = (FDerived*)&Base;						//		｜
		PointerDerived->PublicMethod();										//		｜
		//PointerDerived->DerivedPublicValue = 999;							//	   ◁ 이부분을 수정하면 Base + 0x10 번지인 aa가 수정됨
		//PointerDerived->DerivedPublicValue = 999;
	}
	// virtual
	{
		// 0x0000 : [VTable주소]
		// 0x0008 : int FBase::PublicValue
		// 0x000C : int FBase::ProtectedValue
		// 0x0010 : int FBase::PrivateValue
		// 0x0014 : int FBase::PrivateValue2
		// 
		// 0x0018 : int FDerived::DerivedPublicValue
		// 0x001C : int FDerived::DerivedPublicValue2
		FDerivedVirtual DV;
		DV.PublicMethod();

		FBaseVirtual* BV = &DV;
		BV->PublicMethod();

		Function(&DV);

		FBaseVirtual BV2;
		Function(&BV2);
	}
	// 소멸자를 virtual로 두는 이유
	{
		FBaseVirtual* Instance = new FBaseVirtual;
		FBaseVirtual* Instance2 = new FDerivedVirtual;

		delete Instance;
		// 소멸자도 virtual을 붙히지 않으면 현재 타입 기준으로
		// 소멸자가 호출됨, 즉 FBasedVirtual의 소멸자가 호출됨
		// 원래 타입인 FDerivedVirtual의 소멸자가 호출되도록 하려면
		// virtual을 부모 소멸자에 붙혀야 한다.
		delete Instance2;
	}
	// override,final ,다양한 자식 생성자 특정 부모 생성자 호출 방법
	// Virtual Table address에 생성시 지정한 class의 Virtual Table address가 들어가는 이유
	{
		class FA
		{
		public:
			FA()
				: Value(100)
				, PrivateValue(1000)
			{

			}
			FA(const int InValue)
				: Value(InValue)
			{
				PrivateValue = 0;
			}
			virtual ~FA() {
				std::cout << "FA 소멸 \n";
			}
			//Method에 final이 붙으면 자식에서 override할 수 없다.
			virtual void Method() 
			{
				++PrivateValue;
				std::cout << "FA Method"<< PrivateValue << std::endl;
			}
			
		protected:
			//VTableAddress* Pointer = nullptr; //protected 타입은 아니다
			int Value = 0;
		private:
			int PrivateValue = 0;
		};

		class FB : public FA
		{
		public:
			FB() 
				:FA()
			{
			}
			FB(const int InValue)
				:FA(InValue)
			{
				//protected , public 변수 함수는 자식에서 접근 및 호출가능
				Value = InValue;
			}
			virtual void Method()override final{
				
				FA::Method();			//override한 함수에서 원본 부모 함수를 호출함으로서
										//부모의 기능도 수행하고 추가로 구현한 기능도 수행가능
										//즉,기능의 확장

				std::cout << "FB Method\n";
			}
			~FB() {
				std::cout << "FB 소멸 \n";
			}
		};

		FB B = FB(444);

		class FC final : public FB
		{
		public:
			FC() {
			}
			~FC() {
				std::cout << "FC 소멸 \n";
			}
		};

		FC C = FC();

		// final 이 붙은 class를 상속 할 수없다.
		/*class FB : public FC
		{

		};*/
	}
}