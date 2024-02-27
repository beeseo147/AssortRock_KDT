/*24-02-26
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
        //namesapce : 여러 단체,기업에 코드를 수정
        //이름이 중복될 가능성이 크기 때문에 추가적인 구분을 위해 namespace라는걸 추가

        //변수
        //타입 변수의 이름
        int A =0;
        int B{ 0 };

        std::cin >> A;
        std::cout << "당신이 지정한 숫자 B :" << B <<"  " << A;
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
			char C = 255;
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
			bool b4 = 100; // true

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
			int Int = Float; // 묵시적형변환
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
		{
			Gint = 100;

			//지역 변수는 지금까지 사용한바와 같이 시작과 끝 스코프 {} 내부에서 선언되는 변수를 의미한다
			//유저영역 메모리 공간은 크게 4구획으로 나누어져 있다.
			//[코드   영역] : 소스코드가 기계어로 변환되어 로직을 수행하는 코드정보
			//[데이터 영역] : 전역변수,static 변수 등
			//[Heap]	   : 동적 할당
			//[Stack]      : 지역변수

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
			int a, b, c, d, e, f, g;
			a = 1;
			b = 2;
			c = 3;
			d = 4;
			e = 5;
			f = 6;
			g = 7;

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
