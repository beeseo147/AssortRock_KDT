/*24-02-26
* KIM
솔루션 탐색기 - > 모든 파일 표시로 변경
프로젝트 우클릭 ->속성 -> 중간 디렉토리를 변경
프로젝트 우클릭 ->속성 ->c++20
솔루션(sln) 파일 , 프로젝트(vcxproj) 파일 직접 notepad로 열어서 분석
프로젝트 : xml이라는 문법으로 만들어져있다.

빌드(Build)
	실행 파일을 만드는 과정
		- 전처리(Preprocess) : 소스코드에 담긴 메타정보를 처리한다.
		- 컴파일(Compile) : 소스코드를 머신이 읽을 수 있는 파일로 변환한다.
							(기계어를 어셈블리어로 변환도 포함)
		- 링크(Link) : 컴파일 단계에서 변환한 여러 Object 파일을 Application으로 합친다.
				(우리가 작성한 소스코드들 + 라이브러리 등을 병합)

pba 파일
	-디버깅을 위한정보
	-실제 유저에게 배포할때는 절대로 포함x

컴파일러
	컴파일러 제조사가 컴파일러를 표준 C++문법을 따라서 컴파일 되게 구현한 프로그램
	- MSVC(MicroSoft Visual C,C++) 컴파일러
	- GCC



include 전처리지시자
include 뒤에 나오는 파일을 포함하겠다.
포함이란 ? include 위치에 해당 파일을 복사 붙혀넣기 한다.

*/

#include <iostream>
#include<format>
#include "Function.h"
#include <array>
//#pragma warning(disable:4789)
int Gint{ 10 };

int main()
{
	//브레이크 포인트(Break point) : F5로 실행 (디버거를 붙혀서)하는 경우 해당위치에 도달하면
	//자동으로 멈춰준다
	//-원하는 라인에 캐럿을 두고 F9 으로 실행
	// -또는 원하는 라인 가장 왼쪽에 마우스를 올리기
	//이후 F10으로 한줄씩 실행
	//F5 : 처음에 프로그램을 디버거를 붙혀서 킬 때
	//  켜고난 다음에 F5누르면 다음 Break Point를 만날때 까지 실행

#pragma region 01.cout,cin
	{
		////namesapce : 여러 단체,기업에 코드를 수정
		////이름이 중복될 가능성이 크기 때문에 추가적인 구분을 위해 namespace라는걸 추가

		////변수
		////타입 변수의 이름
		//int A =0;
		//int B{ 0 };

		//std::cin >> A;
		//std::cout << "당신이 지정한 숫자 B :" << B <<"A: ?" << A;
	}
#pragma endregion

#pragma region 02.리터럴(Literal)
	{
		// 리터럴은 코드에 표시한 숫자나 문자열과 같은 값을 의미
		 // 십진수 : 100
		int B{ 100 };
		// 8진수 : 0144   // 거의 쓸일 없음
		int B8{ 0144 };
		// 16진수 : 0x64
		int B16{ 0x64 };
		// 2진수 : 0b01100100 // 거의 쓸일 없음
		int B2{ 0b01100100 };

		// 부동소수점(floating point): 3.14f
		float F{ 3.14f };
		// 배정도 부동소수점(double): 3.14
		double D{ 3.14 };

		// 단일 문자: 'a'
		char C{ 'a' };
		// 문자열: "Hello"

	}
#pragma endregion

#pragma region 03.변수(Variable)*
	{
		// 1Byte == 8비트
		// 2진수로 8비트 같은 경우
		// 2진수: 0000 0000 ~ 1111 1111
		// 10진수: 0~255
		// 1024Byte == 1KB
		// 1024KB == 1MB
		// 1024MB == 1GB
		// 1024GB == 1TB

		// 1000KiB == 1MiB
		// 1000MiB == 1GiB

		// 자료형 (Byte)
		// 정수형: char(1), short(2), int(4), long(4), long long(8), int64(8)
		//      주로사용: char, int
		// 실수형: float(4), double(8)
		{
			int Var{ 0 };   // 초기화 연산자로 변수를 선언과 동시에 초기화 할 수 있다
			Var = 10; // 대입연산자를 사용해서 값을 변경 가능
		}
		{
			// 4byte 정수형 signed를 붙히면 부호가 있는 타입
			// signed는 생략을 하셔도 자동으로 signed
			signed int Var{ -1 };
			Var = Var + 1;

			// unsigned를 붙히면 부호가 없는 타입
			unsigned int Var2{ (unsigned int)-1 };
			Var2 = Var2 + 1;
		}
		{
			// 2Byte 정수형
			// -32,768 ~ 32,767
			short S1{ 32767 };
			S1 = S1 + 1;
			S1 = S1 - 1;

			signed short S2{ 20 };
			unsigned short S3{ 30 };
		}
		{
			// 4Byte 정수형
			long L1{ 14L };
		}
		{
			// 8Byte 정수형
			long long LL1{ 14LL };
			unsigned int I1{ 4294967295 };
			unsigned int I2{ (unsigned int)4294967297 };
			long long LL2{ 4294967296 };
		}
		{
			// 4Byte 실수형
			// 단정도(single) 부동소수점
			// 부동소수점은 컴퓨터에서 부동소수점을 표현하는 특징으로 인해서
			// 부동소수점 오차가 발생할 수 있다
			float F{ 3.14F };
			int I{ (int)3.14F };
		}
		{
			// 8Byte 실수형
			double D{ 3.14 };
		}

		{
			// 1Byte 정수형
			//char C = 255;
			char C0 = 'A'; // ASCII코드 표에 대응되는 수치로 변환해서 저장
			int I = 'A';
			int I2 = 65;

			// https://en.wikipedia.org/wiki/Magic_number_(programming)
			// 프로젝트 속성 -> C/C++ -> 코드 생성 -> 기본 런타임 검사 -> 기본값으로 변경하면 magic value 사라짐


		}

		//부울타입(Boolean) 참과 거짓
		{
			bool b0 = true;
			bool b1 = false;
			bool b2 = 0;
			bool b3 = 1;
			//bool b4 = 100; // true

		}
		//부동 소수점 오차
		{
			double Value = 0;

			if (Value) {
				std::cout << "value 가 0입니다";
			}
			Value = Value + 0.1;
			Value = Value + 0.1;
			Value = Value + 0.1;

			if (Value == 0.3) {
				std::cout << "VALUE가 0.3입니다";

				std::cout << Value;
			}
		}
		// 0으로 초기화 (Zero initailiazation)
		{
			int IntNoint; // 초기화 하지않은 변수

			IntNoint = 10; //초기화가 아님,값을 대입

			int InZeroInit = 0;
			int InzeroInit2{ 0 };
			int InZeroInit3{};
			float Float{};

		}
		// 형변환 Cast : 서로 다른 타입으로 변환
		{
			float Float{ 3.14f };
			//int Int = Float; // 묵시적형변환
			int Int2 = (int)Float; // 명시적 casting,C스타일 cast
			int Int3 = int(Float); // 명시적 casting,C스타일 cast
			int Int4 = static_cast<int>(Float); // C++ 버젼의 명시적 CAST

			//2byte 정수
			short Short{ 10 };
			//4byte 정수
			int Int5 = Short;
			// int(4)rk short(2)보다 더 크고 둘다 정수타입이기 떄문에 경고발생 X

		}
		// 지역 변수와 메모리

		// 지역변수는 지금까지 사용한바와 같이 시작과 끝 스코프({}) 내부에서 선언되는
			// 변수를 의미합니다.

			// 유저영역 메모리 공간은 크게 4구획으로 나누어 져있다고 생각하시면 편합니다
			// [코드영역]	: 소스코드가 기계어로 변환되어 로직을 수행하는 코드정보
			// [데이터영역]	: 전역변수, static 변수 등
			// [Heap]		: 동적 할당
			// [Stack]		: 지역변수

			// [프로그램의 메모리 구조]
			// 낮은주소 0000000.......
			// -------------------- 소스코드 영역 --------------
			// .... 소스코드들...
			// ---------------------데이터 영역  ---------------
			// .... 전역변수, static(정적) 변수
			// --------------------- Heap 영역   ---------------
			// ........ (실행 중에 메모리 할당하는 경우)
			// .......
			// .....
			// ...
			// ..
			// .
			// -------------------------------------------------
			// ....... (지역변수)
			// ........
			// ..........
			// // Return 이후 실행해야 할 주소
			// ....
			// Main함수 RBP(Stack) 주소(미리 변수를 타입과 함께 선언했기 때문에 컴파일러가 해당 함수 Stack에서 어느정도 메모리를 사용할지 알기 때문에 미리 크기를 계산할 수 있다)
			// ....
			// (RBP + 상대 주소) [a](4byte) 
			// (RBP + 상대 주소) [b](4byte) 
			// (RBP + 상대 주소) [c](4byte) 
			// (RBP + 상대 주소) [d](4byte) 
			// (RBP + 상대 주소) [e](4byte) 
			// (RBP + 상대 주소) [f](4byte) 
			// (RBP + 상대 주소) [g](4byte) 
			// 
			// --------------------- Stack 영역 ----------------
			// 높은주소 FFFFFFF.......
		{
			Gint = 100;


			int a, b, c, d, e, f, g;
			a = 1;
			b = 2;
			c = 3;
			d = 4;
			e = 5;
			f = 6;
			g = 7;
		}
		//연산자
		{
			// 단항(unary; 유너리) 연산자: 표현식(expression) 하나를 계산
			// 이항(binary; 바이너리) 연산자: 표현식 2개를 계산
			// 삼항(temary; 텀메리) 연산자: 표현식 3개를 계산

			// 대입 연산자[이항]: 오른쪽 값을 왼쪽의 표현식에 대입하는 연산자
			{
				int i;
				i = 0;	// 대입; i = 0
				int k;
				k = i;	// 대입; k = 0
			}

			// [단항]표현식의 참/거짓 (참: 보통은1, 0이아닌값, 0이면 거짓)
			{
				bool b1{ true };	// 참
				bool b2{ 1 };		// 참
				bool b3{ false };	// 거짓
				bool b4{ 0 };		// 거짓

				bool b5{ !true };	// true의 not(true가 아니다): 거짓
				bool b6{ !false };	// false의 not(false가 아니다): 참

				bool b7{ true };	// true
				bool b8{ !b7 };		// b7(true)의 not: 거짓(false)
			}

			// [이항]사칙연산
			{
				int a{ 1 + 2 };	// 1+2 = 3 = a
				int b{ a + 3 };	// a + 3 = 3 + 3 = 6

				int c{ 1 - 2 }; // 1-2 = -1 = c
				//unsigned int c2{ unsigned int(1 - 2) };

				int d{ c * 3 }; // -1 * 3 = -3 = d

				int e{ 10 / 3 }; // 3
				float f{ 10 / 3 };	// int(10) / int(3) = 3 -> float f = 3;
				float f2{ int(10) / int(3) };
				float f3{ 10.0f / 3.f };
			}

			// [이항]mod, 나머지 연산자
			{
				int m{ 10 % 3 };	// 몫 3, 나머지 1
				int m2{ 5 % 2 };	// 몫 2, 나머지 1
				int m3{ 6 % 2 };	// 몫 3, 나머지 0
			}

			// [단항]후행 / 선행 연산자
			{
				// 후행 증가
				{
					int i{ 0 };
					//i++;
					int k{ i++ }; // k = 0
					// 그리고 나서 i가 ++되어 1이 됩니다
					// k = 0
					// i = 1

					// 식 내부에 후행 연산자를 쓰지 마라
					// 실수 여지가 많다
				}
				// 선행 증가
				{
					int i{ 0 };
					// ++i;
					int k{ ++i }; // k = 1
					// i = 1

					// 이런 선행 수행 연산을 식 내부에 쓰지 마라
					/*++i;
					int k{ i };*/
				}
				// 후행 감소
				{
					int i{ 0 };
					//i--;	// i = -1;
					int k{ i-- }; // k = 0, i = -1
				}
				// 선행 감소
				{
					int i{ 0 };
					//--i;	// i = -1;
					int k{ --i }; // k = -1, i = -1
				}
			}

			// 사칙연산 축약 표현
			{
				int i{ 1 };
				int k{ 2 };

				// i = i + k; // i = {1 + 2} = 3
				i += k; // i = 3
				i += 2;	// i = 5

				i -= 3; // i = i - 3 = 5 - 3 = 2

				i *= 2; // 2 * 2 = 4
				i /= 2; // 4 / 2 = 2
				i %= 2;	// 2 % 2 = 0
			}

			// 비트 단위 연산
			{
				// AND 연산
				{
					// 둘다 1이면 1이고, 하나라도 0이면 0이다
					// 0010
					// 1111
					// ------ AND
					// 0010
					char c = 2;
					char c2 = 15;
					char c3 = c & c2;	// 2
				}
				// OR 연산
				{
					// 둘중에 하나라도 1이면 1이고, 둘다 0이면 0
					// 0010
					// 1111
					// ------ OR
					// 1111
					char c = 2;
					char c2 = 15;
					char c3 = c | c2; // 15
				}
				// XOR 연산(exclusive or)
				{
					// 서로 다르면 1, 같으면 0
					// 0010
					// 1111
					// ------ XOR
					// 1101		-> 1(2^0) + x(2^1) + 4(2^2) + 8(2^3) = 13
					char c = 2;
					char c2 = 15;
					char c3 = c ^ c2;	// 13
				}
			}
		}

	}
#pragma endregion

#pragma region 04.열거형(enumerated type, enum)*
	{
		{
			// const: 상수(constant), 초기화 이후 해당 값을 변경할 수 없다
			const int Iron = 0; //Iron = 10;
			const int Bronze = 1;
			const int Silver = 2;
			const int Gold = 3;

			int MyTier = Gold;
		}
		{
			enum /*class*/ ETier : unsigned char
			{
				Iron /*= 10*/
				, Bronze
				, Silver /*= 20*/
				, Gold
			};

			// class키워드를 enum에 붙혀두면 cast를 해야 다른 type에 값을 넣을 수 있다
			unsigned char MyTier = (unsigned char)ETier::Gold;
			ETier MyTier2 = ETier::Bronze;
			ETier MyTier3 = (ETier)0;	// ETier::Iron

			if (MyTier2 == ETier::Bronze)
			{
				std::cout << "Bronze\n";
			}

			if (MyTier == ETier::Gold)
			{
				std::cout << "Gold\n";
			}
		}
	}
#pragma endregion
#pragma region 05.구조체(struct)***
	{
		enum class ETier : unsigned char
		{
			None,
			Iron,
			Bronze,
			Silver,
			Gold,
		};

		/*int HP = 10;
		int MP = 0;*/
		// 구조체를 사용하면 데이터를 묶어서 들고 있을수 있게 한다
		struct FPlayer
		{
			int HP;// = 10;
			int MP = 0;
			ETier Tier = ETier::None;
			// 3Byte
		};

		// FPlayer: 구조체 타입
		// Player: 인스턴스(instance; 실체화된 사례) (메모리에 만들어진 것)
		FPlayer Player{ .HP = 100, .MP = 20 };
		Player.HP = 100;
		Player.MP = 30;
		Player.Tier = ETier::Gold;

		// 컴파일 타임에 size를 계산해서 변수에 저장한다
		int Size = sizeof(FPlayer);
		int Size2 = sizeof(Player);
		//int Size3 = sizeof(long long);
		std::cout << "[Player Info]\n";
		//std::cout << "HP: " << Player.HP << "MP: " << Player.MP << std::endl;
		std::cout << std::format("HP: {}, MP: {}\n", Player.HP, Player.MP);
		//std::cout << Player.Tier;
		std::cout << std::format("Tier: {}\n", (int)Player.Tier);

		struct FPadding
		{
			char C;
			// Padding에 의해 3Byte 가 숨겨져 있다
			// 지금 가장 큰 기본 자료형 크기가 4Byte라서 4Byte 기준으로 4Byte보다 작은 경우 
			// padding이 생긴다

			char C2;
			char C3;
			char C4;
			// 4byte ----------

			char C5;
			// padding 3Byte
			// 8Byte-----------

			// padding은 바꿀 수 있다(padding이 생기지 않도록 처리할 수 있습니다)
			int I;
			// 12Byte ---------
		};

		struct FPadding2
		{
			char c;	// 1Byte
			// 7Byte padding

			double b;	// 8Byte
		};
		// 64bit(8Byte) 환경에서 한번에 접근해서 연산할수 있는 최대 단위가 8byte
		// padding을 비활성화 해서 다음과 같이
		// char / double (9)
		// [00] / [00 00 00 00 00 00 00 00]
		// [00] / [00 00 00 00 00 00 00]    // [00]
		// double에 값을 쓰거나 읽으려고 했을때 padding이 잡혀있지 않으면
		// 2번 접근해야 하는 상황이 발생할 수 있다.
		// 그렇기 때문에 읽고 쓰는 속도가 느려질 수 있다.
	}
#pragma endregion

#pragma region 06.조건문(if / switch)***
	{
		// if
		{
			//int Value = 0;
			//std::cin >> Value;

			//// if 조건이 true if내부로 실행
			//// if 조건이 false else 실행
			//// else는 없을 수 있다
			//// 조건문을 사용하면 어떤 값이 참 또는 거짓인지에 따라 원하는 코드를 실행하는 문법
			//if (Value == 100)
			//{
			//	std::cout << "Value가 100입니다\n";
			//}
			//else
			//{
			//	std::cout << std::format("Value: {} 입니다\n", Value);
			//}

			// if(<초기자>;<조건문>)
			// if 조건이 true이면 if 내부로 실행
			// if 조건이 false이고, else if 조건이 만족하면, else if가 실행이 됩니다.
			// 전부 만족하지 않는 경우 else 가 실행 됩니다.
			if (int i = 10; i < 10)
			{
				std::cout << "1\n";
			}
			else if (i == 13)
			{
				std::cout << "2\n";
			}
			else if (i == 12)
			{
				std::cout << "3\n";
			}
			else if (i == 10)
			{
				std::cout << "4\n";
			}
			else
			{
				//i = 10000;
				std::cout << "5\n";
			}
		}

		// switch
		{
			enum class ETier : unsigned char
			{
				None,
				Iron,
				Bronze,
				Silver,
				Gold,
			};

			struct FPlayer
			{
				int HP = 100;
				int MP{ 10 };
				ETier Tier = ETier::None;
			};
			FPlayer Player;
			Player.Tier = ETier::Gold;
			std::cout << "[Player Info]\n";
			std::cout << std::format("HP: {}, MP: {}\n", Player.HP, Player.MP);
			//std::cout << std::format("Tier: {}\n", (int)Player.Tier);
			switch (Player.Tier)
			{
			case ETier::None:
				std::cout << "Tier: None\n";
				break;
			case ETier::Iron:
				std::cout << "Tier: Iron\n";
				break;
			case ETier::Bronze:
				std::cout << "Tier: Bronze\n";
				break;
			case ETier::Silver:
				std::cout << "Tier: Silver\n";
				break;
			case ETier::Gold:
				std::cout << "Tier: Gold\n";
				break;
			default:
				std::cout << "default\n";
				break;
			}

			if (Player.Tier == ETier::None)
			{
				std::cout << "Tier: None\n";
			}
			else if (Player.Tier == ETier::Iron)
			{
				std::cout << "Tier: Iron\n";
			}
			else if (Player.Tier == ETier::Bronze)
			{
				std::cout << "Tier: Bronze\n";
			}
			else if (Player.Tier == ETier::Silver)
			{
				std::cout << "Tier: Silver\n";
			}
			else if (Player.Tier == ETier::Gold)
			{
				std::cout << "Tier: Gold\n";
			}
			else
			{
				std::cout << "defaultn";
			}

			Player.Tier = ETier::Iron;
			switch (Player.Tier)
			{
			case ETier::None:
				std::cout << "분발하세요";
				[[fallthrough]];//에트리뷰트
			case ETier::Iron:
			case ETier::Bronze:
			case ETier::Silver:
				std::cout << "[Silver]";
				break;
			case ETier::Gold:
				std::cout << "[Gold]";
				break;
			default:
				break;
			}

			Player.Tier = ETier::Silver;
			//Tier 가 Iron 도는 Bronze인가요?
			if (Player.Tier == ETier::Iron
				|| Player.Tier == ETier::Bronze
				|| Player.Tier == ETier::Silver)
				//(
				// // 나는 Silver
				// Player.Tier == ETier::Iron  -> 거짓 (0)
				// || Player.Tier == ETier::Bronze -> 거짓 (0)
				// || Player.Tier == ETier::Silver -> 참 (1)
				//	)
				// 0 || 0 || 1
				// 0 || 1
				// 1
			{
				if (Player.Tier == ETier::Iron) {
					std::cout << "분발하세요";
				}
				std::cout << "Iron,Bronze,Silver\n";
			}
		}
	}
#pragma endregion
#pragma region 07.논리연산자*
	{
		// 논리 부정
		if (!false) // true
		{
			std::cout << "!false";
		}

		// 논리곱(AND)
		// && : AND양쪽 조건이 모두 참인경우 true / 하나라도 거짓인 경우 false
		int a = 10;
		int b = 20;
		// 1. a == 10 ? true
		// 2. b == 10 ? false
		// 3. true && false => false
		//if (a == 10 && b == 10)

		// 1. a == 10 ? true
		// 2. b == 20 ? true
		// 3. true && true => true
		if (a == 10 && b == 20)
			// if ((a == 10 || a == 15) && b == 20)
		{
			std::cout << "a && b\n";
		}
		else
		{
			std::cout << "not a && b\n";
		}

		// 논리합(OR)
		// 1. a == 10 ? true
		// 2. 내부로 진입
		// b를 판단할 필요 없어 a가 이미 참이므로 내부로 진입한다
		if (a == 10 || b == 10)
		{
			std::cout << "a || b\n";
		}

		// 1. b == 10 ? false
		// 2. a == 10 ? true
		// 3. false || true => true
		if (b == 10 || a == 10)
		{
			std::cout << "a || b\n";
		}

		// 1. b == 500 ? false
		// 2. a == 2000? false
		// 3. false || false => false
		if (b == 500 || a == 2000)
		{
			std::cout << "a || b\n";
		}
		else
		{
			std::cout << "not a || b\n";
		}

		a = 10;
		b = 20;
		int c = 100;
		// 1. a == 10 ? true
		// 2. b == 20 ? true
		// 3. c == 100? true
		// true && true && true => true
		if (a == 10 && b == 20 && c == 100)
		{
			std::cout << "a && b && c\n";
		}

		// 1. a == 10 ? true
		// 2. (b == 50 || c == 100) ? true
		//	   b == 50 ? false
		//	   c == 100? true
		//	   false || true => true
		// 3. true(a==10) && (false || true)
		//    true && true => true
		if (a == 10 && (b == 50 || c == 100))
		{
			std::cout << "a && (b || c)\n";
		}

		if (First())
		{
			std::cout << "First!\n";
		}

		if (First() || Second())
		{
			std::cout << "First || Second\n";
		}

		if (Second() || First())
		{
			std::cout << "Second || First\n";
		}

		const bool bFirst = First();
		const bool bSecond = Second();
		//bSecond = false;
		if (bFirst || bSecond)
		{
			std::cout << "First || Second !\n";
		}
	}
#pragma endregion

#pragma region 08.함수(function)***
	{
		// 규모가 큰 프로그램에서 모든 코드를 main함수 안에 담게 되면 관리가 힘들 것 같습니다.
		// 코드 가독성(읽기 쉬운 정도)을 높이려면 코드를 간결하고 명확한 함수 단위로 나누는 것이 좋겠습니다.

		// C++에서 함수를 사용하려면 먼저 선언을 해야 합니다.
		// 반환타입		함수이름	(입력 파라미터(옵션))
		// void			FunctionName(int a, int b, ...)

		// 선언만 하고 구체적인 동작을 구현(정의)하지 않은 채 함수를 호출한 문장이 담긴 코드를 컴파일하면
		// 존재하지 않는 함수를 호출하기 때문에 링크 과정에서 에러가 발생합니다.

		// 디버거가 붙어있는 상황에서 F11을 눌러서 함수 내부로 진입할 수 있다
		FunctionName();

		// 이 함수를 호출하는 위치 기준으로 이 라인보다 위에 함수가 있다는 것을 
		// 알려주지 않으면 함수를 찾을수 없습니다.

		// 함수도 주소가 있고
		// 함수를 호출한다는건
		// >>> 돌아올 다음주소를 Backup해두고
		// >>> 함수의 주소로 이동했다가
		// >>> 그 함수를 수행하고
		// >>> ret을 만나면 Backup해둔 주소로 이동한다
		FunctionName();
		int a = 10;
		// 콜링컨벤션(Calling Conventions)
		// 함수를 호출하는 방법에 대한 종류
		// __cdecl, __stdcall, __thiscall, __fastcall

		// 파라미터를 던지는 경우 특정 레지스터(메모리)에 값을 backup했다가
		// 함수 내부로 진입해서 그 레지스터(메모리)에서 다른 메모리로 값을 복원한다.
		// 이런것을 함수 호출의 오버해드라고 한다.
		FunctionName(a);

		int Result = AddFunction(10, 20);
		int Result2 = AddFunction(11, 30);
		int Result3 = AddFunction(15, 40);
		int Result4 = AddFunction(3, 2);
		int Result5 = AddFunction(1, 3);
		AddFunction(10, 20);

		double Result6 = AddFunction(3., 2.45);

		unsigned long long Ret = Factorial(4);
		std::cout << std::format("{}\n", Ret);

	}
#pragma endregion

#pragma region 09.Bit Flag
	{
		unsigned char Property1 = EproertyFlags::Eproperty1;
		HasFlag(Property1);
		unsigned char Property3 = EproertyFlags::Eproperty3;
		HasFlag(Property3);
		unsigned char Property13 = EproertyFlags::Eproperty1 | EproertyFlags::Eproperty3;
		HasFlag(Property13);

		//신규 속성을 추가하기 위해 OR(|) 연산 사용
		Property13 |= EproertyFlags::Eproperty7;
		HasFlag(Property13);
		unsigned char NotProperty7 = ~EproertyFlags::Eproperty7;
		//0100 0000		: EproertyFlags::Eproperty7;
		//1011 1111		: ~EproertyFlags::Eproperty7;
		//---------AND
		//0000 0101
		//특정 속성을 뺀다

		Property13 = Property13 & ~EproertyFlags::Eproperty7;
		HasFlag(Property13);

		//XOR : 서로 다르면 1, 같으면 0
		//0000 1010
		//0000 1000
		//------XOR
		//0000 0001
		//0000 1000
		//------XOR
		//0000 1001

		unsigned char Togle = Eproperty2 | Eproperty4;
		HasFlag(Togle);
		Togle = Togle ^ Eproperty4;
		HasFlag(Togle);
		Togle = Togle ^ Eproperty4;
		HasFlag(Togle);
		Togle = Togle ^ Eproperty4;
		HasFlag(Togle);

		unsigned char Value = EproertyFlags::ENone;
		//지정
		Value = EproertyFlags::Eproperty1;

		//켜기
		Value = Value | EproertyFlags::Eproperty2;

		//끄기
		Value = Value & ~EproertyFlags::Eproperty2;

		//토글(껏다 켯다)
		Value = Value ^ EproertyFlags::Eproperty4;		//켜짐
		Value = Value ^ EproertyFlags::Eproperty4;		//꺼짐
		Value = Value ^ EproertyFlags::Eproperty4;		//켜짐

	}
#pragma endregion
#pragma region 10.배열(array)
	{
		int a{}, b{}, c{};
		a = 1;
		b = 2;
		c = 3;

		// 1차원 배열
		{
			// 3개가 있다
			int Array[4]{ 56,4,03 };
			int d = -1;
			// 0번 index(또는 원소)에 1을 넣겠다
			Array[0] = 1;
			Array[1] = 2;
			Array[2] = 3;
			// Array의 시작 주소에서 Size * index
			// 메모리에 접근하겠다
			Array[3] = 4;
			//Array[4] = 5; // ?

			int Size = sizeof(int);	// 4byte
			int ArraySize = sizeof(Array);
			int ArrayElemSize = sizeof(Array[0]);
			// 하나의size = 총size / 하나의 size
			int ArrayElemCount = ArraySize / ArrayElemSize;
		}
		// 2차원 배열
		{
			// Array[0][0] Array[0][1] Array[0][2] ...
			int Array[2][3]{};
			Array[0][0] = 1;
			Array[0][1] = 2;
			Array[0][2] = 3;
			Array[1][0] = 4;
			Array[1][1] = 5;
			Array[1][2] = 6;
		}
		// std::array (컨테이너)
		{
			// int Array[3];
			std::array<int, 3> Array{ 1,3,6 };
			Array[0] = 1;
			Array[1] = 2;
			Array[2] = 3;
			// typedef는 왼쪽에 있는 타입을 오른쪽에 있는
			// 것으로 바꿔서 쓸 수 있게 해준다
			//typedef unsigned __int64 hi;
			size_t Size = Array.size();
			size_t TotalSize = sizeof(Array);
		}
	}
#pragma endregion

#pragma region 11.반복문(Loop) ***
	{
		{
			int i = 0;
			while (i < 5)
			{
				std::cout << std::format("i값은: {}\n", i);
				++i; // i = i + 1;

				if (i == 3)
				{
					std::cout << std::format("i가 3일때 탈출!\n");
					break;
				}
			}
		}
		{
			int i{ 30 };
			do
			{
				std::cout << std::format("i값은: {}\n", i);
				++i;
			} while (i < 5);	// false일때 탈출
			// 31 < 5 => false
		}
		{
			int length = 5;
			for (int i = 0; i < length; ++i)//, First())
			{
				std::cout << std::format("i값은: {}\n", i);
			}

			const int Size = 6;
			int Array[Size]{};
			for (int i = 0; i < Size; ++i)
			{
				Array[i] = i;
			}

			// 범위기반 for(range based for)
			for (int i : Array)
			{
				//i = 10000;
				std::cout << std::format("i 값은: {}\n", i);
			}

			std::array<int, Size> StdArray{};
			for (size_t i = 0; i < Size; ++i)
			{
				StdArray[i] = i;
			}

			for (int i : StdArray)
			{
				std::cout << std::format("i 값은: {}\n", i);
			}

			// C++20
			// CTAD(class template argument deduction; 클래스 템플릿 인수 추론)
			for (std::array Array2{ 1,2,3 }; int i : Array2)
			{
				std::cout << std::format("i 값은: {}\n", i);
			}
		}
	}
#pragma endregion

#pragma region 12.포인터와 동적 메모리(Pointer***,dynamic memory)+ 레퍼런스***(Reference : 참조)
	{
		// 메모리 할당과 관리하는 것은 C++프로그래밍에서 문제가 발생하기 쉬운 영역입니다.
		// 품질이 뛰어난 C++프로그램을 작성학기 위해서는 메모리 내부 작동 방식을 이해하고 있어야 합니다
		// 이번 시간에는 동적 메모리를 다루는 과정에서 어떤 위험에 빠지기 쉬운지 알아보고 이런 상황을
		// 해결하거나 애초에 방지하는 방법을 알아보겠습니다.

		// low-level(저수준; 낮은수준) 메모리 연산 방법은 new, new[], delete, delete[]
		// 또는 C스타일의 malloc(malloc allocation), free라는 함수를 사용하는 방법이 있습니다.
		// 요즘 와서는 로우레벨 메모리 연산을 최대한 피하는 추세라고 생각됩니다.
		// 저도 최근 몇년간 저수준의 동적 할당을 해본 경험이 손에 꼽을 수준인 것 같습니다.
		// 예를 들면 표준 라이브러리에서 제공하는 vector라는 컨테이너(동적 배열)가 있는데
		// 이를 사용하면 필요할 때 메모리를 늘리거나 줄일 수 있습니다.
		// 또는 동적으로 할당한 메모리를 사용하지 않으면 자동으로 해제해주는 shared_ptr 등의
		// 스마트 포인터를 사용하기도 합니다.

		// 동적 메모리를 이용하면 컴파일 시간에 크기를 확정할 수 없는 데이터를 다룰 수 있습니다.
		{
			// 지역변수는 지금까지 사용한바와 같이 시작과 끝 스코프({}) 내부에서 선언되는
			// 변수를 의미합니다.

			// 유저영역 메모리 공간은 크게 4구획으로 나누어 져있다고 생각하시면 편합니다
			// [코드영역]	: 소스코드가 기계어로 변환되어 로직을 수행하는 코드정보
			// [데이터영역]	: 전역변수, static 변수 등
			// [Heap]		: 동적 할당
			// [Stack]		: 지역변수

			// [프로그램의 메모리 구조]
			// 낮은주소 0000000.......
			// -------------------- 소스코드 영역 --------------
			// .... 소스코드들...
			// ---------------------데이터 영역  ---------------
			// .... 전역변수, static(정적) 변수
			// --------------------- Heap 영역   ---------------
			// ........ (실행 중에 메모리 할당하는 경우)
			// .......
			// .....
			// ...
			// ..
			// .
			// -------------------------------------------------
			// ....... (지역변수, 함수 복귀주소 등)
			// 
			// A
			// ->
			// Main
			// --------------------- Stack 영역 ----------------

			// 실행시간(런타임;run time)에 동적으로 메모리 공간이 필요한 경우 OS(운영체제;Operating System)
			// 에 메모리를 요청해야 하는데, 이런 과정에서 커널에 요청할 필요가 있습니다.
			// 커널은 OS 중 항상 메모리에 올라가 있는 운영체제의 핵심 부분으로, 하드웨어와 응용 프로그램
			// 사이에서 인터페이스 역할을 제공합니다.
			// 커널에 요청하는 경우 이를 system call이라고 합니다. (메모리 할당을 할때마다 system call이 발생
			// 하지는 않을 수 있습니다)
			// 이 system call은 유저 영역과 커널 영역을 넘나드는 호출로서 상당한 비용을 지불하게 됩니다.
		}

		{
			// 64비트 일때는 포인터의 크기는 8byte
			// 32비트 일때는 포인터의 크기는 4byte
			// [Stack]										// [Heap]
			// [0xfff] Pointer(8Byte; 64bit) = nullptr
			// 주소를 들고 있을 것이다. 그 주소를 찾아가면 int가 있다
			int* Pointer{ nullptr };	// 실제 값은 0, 프로그래머를 위해 0을 쓰는 것 보다
			// nullptr을 넣어주면 명확한 의미를 전달할 수 있다.

			// 포인터의 크기는 플랫폼 bit수에 대응해서 바뀜
			// 32bit라면 최대 표현 가능한 주소가 FFFF FFFF(10진수로 4,294,967,295) 으로 unsigned int범위에
			// 해당한다. 즉 4byte이다
			// 64bit라면 FFFF FFFF FFFF FFFF 8byte까지 표현할 수 있기 때문에.
			// 
			// int*의 의미는 지금 내가 가지고 있는 주소(*)로 가면 그 값은 int야 라는 의미입니다.
			// char* 라면 내가 가지고 있는 주소는 8byte 주소이지만, 그 주소로 가면 char 타입의 변수가 있다
			size_t Size = sizeof(int*);
			size_t Size2 = sizeof(char*);
		}
		{
			int a = 100;
			// [Stack]										// [Heap]
			// [0xfff] Pointer(8Byte; 64bit) = nullptr		
			int* Pointer{ nullptr };
			int b = 10;

			// [Stack]										// [Heap]
			// [0xfff] Pointer(8Byte; 64bit) = 0x100		0x100 int[4byte] = 10
			Pointer = new int{ 10 };

			// [Stack]										// [Heap]
			// [0xfff] Pointer(8Byte; 64bit) = 0x100		0x100 int[4byte] = 10000
			*Pointer = 10000;
			std::cout << *Pointer << a << std::endl;
			//Pointer = (int*)10000;	// 잠재적인 문제가 발생할 가능성이 아주 높다
			//*Pointer = 500;
			// 이렇게 동작할당을 하고 Memory를 해제하기 전에 다른 주소로 바꾸는 경우
			// 할당한 메모리는 미아가 됩니다.
			// 이를 메모리 누수(메모리 릭, memory leak)이라고 부릅니다.

			// memory 할당 해제
			delete Pointer;
		}
		{
			//[Stack]									//[Heap]
			//[0x???] Pointer(8Byte;64bit) = 0x100
			int* Pointer{ new int(5) };
			//메모리 누수(메모리 릭,memory leak)

			//delete를 해줌으로서 메모리 누수를 막 을 수있다.
			delete Pointer;
		}
		{
			//C언어를 배웠다면 malloc을 사용해서 메모리르 할당 했을텐데,C++에서도 사용 가능하다
			//malloc과 new는 큰 차이가 없다.
			//아직 배우지 않았지만,new와 delete는 struct 또는 class에서 생성자 소멸자를 호출한다
			//그러나 malloc은 순수하게 memory만 할당 해줍니다.
			//int* 입장에서도 new는 초기값{}을 지정할 수 있었지만,malloc은 지정불가!
			int* Pointer = (int*)malloc(sizeof(int));
			*Pointer = 1000;
			free(Pointer);
		}

		{
			// 메모리 할당이 실패할 수도 있습니다.
			// 컴퓨터에 메모리가 부족한 경우 동적 할당은 실패할 수 있습니다.
			// nullptr
			//while (true) {
			//	new int;
			//}
		}
		{
			// [Stack]										// [Heap]
			// [0xfff] Array(8Byte; 64bit) = 0x100			0x100 [int][int][int][int][int][int]
			// 
			// 배열 동적 할당
			int* Array = nullptr;
			Array = new int[6] {0, 1, 2, 3, 4, 5};
			Array[0] = 100;
			*Array = 10;
			//Array가 들고 있던 주소로부터 1칸을 이동하는데 1칸이 지금 타입이 int*
			//이기때문에 4byte만큼 건너뛴 위치의 값을 20으로 int만큼 바꾼다

			*(Array + 1) = 20;
			//Array가 들고 있던 주소로부터 1칸을 이동하는데 1칸이 지금 타입이 __int64*
			//이기때문에 8byte만큼 건너뛴 위치의 값을 100으로 __int64만큼 바꾼다
			//*((__int64)Array +1) =10;

			for (int i = 0; i < 6; ++i)
			{
				Array[i] = i + 1;

				// Array + n
				// Array(Heap에 있는 주소) + n
				// Array + 1 = Array주소에 + 4byte(int)의 주소

				// Array(int*)	Array + 1    Array + 2    Array + 3 ...
				// [00 00 00 01][00 00 00 02][00 00 00 03][00 00 00 04]

				*(Array + i) = i + 2;
			}
			delete[] Array;
		}
		// 2차원이상 배열도 동적할당으로 구현이 가능합니다.
			// 저는 실무에서 쓴 기억이 없습니다.
		{
			// [Stack]										// [Heap]
			// [0xfff] Array(8Byte; 64bit) = 0x100			0x100 [int][int][int][int][int][int]
			// 
			// 배열 동적 할당
			char* Array = nullptr;
			Array = new char[6] {0, 1, 2, 3, 4, 5};
			Array[0] = 100;
			for (int i = 0; i < 6; ++i)
			{
				Array[i] = i + 1;

				// Array + n
				// Array(Heap에 있는 주소) + n
				// Array + 1 = Array주소에 + 4byte(int)의 주소

				// Array(char*)	Array + 1    Array + 2    Array + 3 ...
				// [01]         [02]         [03]         [04]
				//int* Test = (int* )Array;
				// i offset 만큼 떨어진 위치의 값을 바꾸기겠다
				*(Array + i) = i + 2;
				// 리틀엔디안 빅엔디안 (컴퓨터 내부에서 비트를 처리하는 방식)
				//*(Test + 1) = 5;
			}
			delete[] Array;
		}
		{
			int a = 10;
			int* Pointer = nullptr;
			Pointer = &a;
			*Pointer = 100;
			std::cout << "*Pointer : " << *Pointer << " Pointer : " << Pointer << " &Pointer : " << &Pointer << "a : " << a;
		}
		{
			struct Fstruct
			{
				//생성자 : 인스턴스가 만들어질 때 호출되는 함수
				//자동 생성
				//thiscall : 자기자신의 주소를 파라미터로 던져준다.
				Fstruct(/*Fstruct*This*/) {
					std::cout << std::format("V1 : {} V2 : {}", this->Value, this->Value2);
				}

				int Value = 10;
				int Value2 = 100;

				void Print() {
					std::cout << std::format("V1 : {} V2 : {}", Value, Value2);
				}
				//자동 생성
				~Fstruct() {
					std::cout << "소멸 했어요";
				}

			};
			int V0 = 20;
			// int[Value = 10]
			// int[Value2 = 100]
			Fstruct Struct;
			Fstruct Struct2;

			Struct.Value = 1000;
			Struct.Print();
			Struct2.Print();
			int V1 = 200;

			Fstruct* Pointer = new Fstruct;
			Pointer->Value = 1000;
			(*Pointer).Value2 = 10000;
			
			int* Pointer1 = (int*)Pointer;
			*Pointer1 = 444;
			int* Pointer2 = Pointer1 + 1;
			*Pointer2 = 555;

			
			delete Pointer;
			{
				//malloc은 요청한 size만큼 메모리 블록만 할당
				//new는 요청한 size만큼 메모리 블록할당 후 초기화(struct같은 경우 생성자까지 호출)
				Fstruct* Struct2 = (Fstruct*)malloc(sizeof(Fstruct));
				free(Struct2);
			}

			// 저소준의 동적할당은 사용빈도가 줄었다
			// 포인터는 사용하지 않은날이 없는 수준
		}

	}
#pragma endregion
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
