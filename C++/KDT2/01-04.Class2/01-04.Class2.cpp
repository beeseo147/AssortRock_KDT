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

	// interface 상속
	// 순수 가상 함수
	{
		class FA
		{
		};

		class FB : public FA, public IInterface
		{
		public:
			virtual void MustFunction() override
			{
				std::cout << __FUNCTION__ << std::endl;
			}

		public:
			int Value = 1;
		};

		FB B;
		//B.IInterface::Value = 10;
		B.MustFunction();
		B.MustFunction2();

		class FC : public IInterface
		{
			virtual void MustFunction() override
			{
				std::cout << __FUNCTION__ << std::endl;
			}

			virtual void MustFunction2() override
			{
				IInterface::MustFunction2();
				Value = 200;
				std::cout << Value << std::endl;
			}

			int Value = 100;
		};

		FC C;

		FunctionMustInterface(&C);

		std::vector<IInterface*> Vector;
		Vector.reserve(2);
		Vector.push_back(&B);
		Vector.push_back(&C);

		for (IInterface* It : Vector)
		{
			It->MustFunction();
			It->MustFunction2();
		}
	}

	//C++ cast
	{
		//static_cast<>
		//const_cast<> :const를 일시적으로 제거할 수 있다.
		//reinterpret_cast
		//dynamic_cast

		//static cast : 명시적 변환
		{
			int i{ 3 };
			int k{ 4 };
			double Result = static_cast<double>(i)/k;

			class FA {
			public:
				FA() = default;
				FA(const FA&) = delete;
			};
			class FB : public FA
			{
			public :
				int Value2 = 0;
			};
			FA* A = new FA;
			// down cast, 지금은 문제가 많음
			FB* B = static_cast<FB*> (A);

			// up cast
			A = B;

			delete A;

			int* Int = new int;
			// static_cast는 생각만큼 강하지 않음
			// 서로 관련이 없는 포인터 타입의 경우 static_cast를 사용할 수없다
			//double* Double = static_cast<double*>(Int);
			//short* Short = static_cast<short*>(Int);
			delete Int;
		}

		//reinterpret_cast : static_cast 보다 강력(자유도)하지만 안전성이 떨어진다
		{
			int* Int = new int;
			
			double* Double = reinterpret_cast<double*>(Int);
			short* Short = reinterpret_cast<short*>(Int);
			delete Int;
		}

		// dynamic_cast : 실행시간(런타임)에 type을 검사해서 관련이 있으면 변환
		// 관련이 없으면 nullptr로 초기화
		// virtual talbe이 있어야 가능
		{
			class FA
			{
			public:
				FA() = default;
				FA(const int InA) {}
				FA(const FA&) = delete;
				virtual ~FA() = default;
			};
			class FB : public FA
			{
			public:
				int Value2 = 0;
			};
			class FC
			{
				virtual ~FC() = default;
			};

			FA* A = new FA;
			FA* AB = new FB;

			//Down cast
			//RTTI(RunTime Type Information) 기술을 기반으로
			//실행 시간에 타입을 검사해서 Cast 여부를 판단
			//virtual table이 있어야 동작
			FB* B = dynamic_cast<FB*>(A);
			if (B) {
				std::cout << "Cast Succeessed\n";
			}
			else {
				std::cout << "Cast failed\n";
			}

			B = dynamic_cast<FB*>(A);
			if (B) {
				std::cout << "Cast Succeessed\n";
			}
			else {
				std::cout << "Cast failed\n";
			}
			
		}
	}
	// 객체지향 프로그래밍(Object-Oriented Programming(OOP))
	{
		// C++ class, struct OOP의 핵심 요소라고 할 수 있다.

		// - 캡슐화(encapsulation)
		// 변수와 함수를 하나의 단위로 묶는 것을 의미합니다.

		// - 정보 은닉(information hiding)
		// 프로그램의 세부 구현을 외부로 드러나지 않도록 특정 모듈 내부로 감추는 것
		// 접근 지정자(private, protected, public)가 그 중 하나

		// - 상속(inheritance)
		// 상속은 자식 클래스가 부모 클래스의 특성과 기능을 그대로 물려받는 것을 말한다
		// overriding: 기능의 일부분을 변경해야 할 경우 자식 클래스에서 상속받는
		// 기능만 수정해서 다시 정의할 수 있다.
		// 상속은 캡슐화를 유지하면서 클래스의 재사용이 용이하도록 해 준다.

		// - 다형성(polymorphism)
		// 하나의 변수나 함수가 상황에 따라 다른 의미로 해석될 수 있는 것을 말한다.
	}
}