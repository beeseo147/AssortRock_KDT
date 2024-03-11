// 01-02.String.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include<format>
#include<string>
#include<Windows.h>

int main()
{
#pragma region C스타일의 문자열
	{
		char String1[6]{ "Hello" };
		char String11[11];
		std::cout << String1 << std::endl;
		String1[0] = 'W';
		String1[2] = 'a';
		//String1[9] = 'B';//버퍼 오버플로우(Buffer overflow)
		char* Pointer = String1;
		*(Pointer + 1) = 'A';
		//*(Pointer + 9) = 'A'; // Buffer overflow
		//String1 = String11; //안된다
		/* 장점
		*  -간단하다
		*  -가볍다.메모리를 꼭 필요한 만큼만 사용한다
		*  -저수준(low level)이다.메모리 조작이 쉽다.
		* 단점
		*  -편의 기능(복사,사이즈확인 등등)을 관련 기능을 찾거나 따로 구현해야 함
		*  -
		*/

		const char* String2 = "Hello";

		const char* String3 = "Hello";

	}
#pragma endregion

#pragma region C++스타일의 문자열(String)
	{
		std::string A = "Hello";
		std::string B = "World";
		std::string C = A + B;

		A += B;
		A.append(B);
	}
	{
		const char* A{ "Hello" };	//Data에
		const char B[]{ "Hello" };	//Stack memory에
		const char* C{ "Hello" };	//Data에 //A,C는 동일한 주소를 가리킴

		if (A == B) {	//메모리 주소에 대한 비교
			std::cout << "A==B\n";
		}
		else
		{
			std::cout << "A!=B\n"; //메모리주소가 다름
		}
		if (A == C) {
			std::cout << "A==C\n"; // 메모리주소가 같음
		}
		else
		{
			std::cout << "A!=C\n";
		}
		bool bSame = true;
		for (int i = 0; i < 5; i++) {
			if (A[i] != B[i]) {
				bSame = false;
				break;
			}
		}

		if (bSame)

		{
			std::cout << "Same\n";
		}
		else
			std::cout << "not same\n";

		const int Result = strcmp(A, B);
		if (Result == 0) {
			std::cout << "Same\n";
		}
		std::string AA{ "Wow" };
		std::string BB{ "Wows" };
		if (AA == BB) {
			AA._Equal(BB);
		}
	}
	{
		// - 시간 및 언어 -> 언어 및 지역 -> 기본 언어 설정 -> (국가 또는 지역) -> 관리자 옵션 -> 시스템 로캘 변경(Beta UTF-8)
		// - Visual stduio 우측 상단 -> 파일 -> 다른 이름으로 xx저장 -> 다이얼로그 우측 하단 저장 버튼 오른쪽에 있는
			// 화살표 클릭 -> 인코딩 하여 저장 -> UTF-8로 되어 있는지 확인해야 문제가 없습니다.
		// 한국 로캘에서는 기본적으로 한국어 코드페이지(949)로 되어 있으나 이러면 한글 주석, 문자열 등이
		// 깃 등에 업로드 하면 깨져서 나옵니다.

		// visual studio에서 .editconfig라는 파일을 만들어서 원하는 확장자 파일의 코드 페이지를 설정하면
		// 신규로 만드는 파이르이 경우 해당 코드 페이지를 사용하게 됩니다.

		//TCHAR Char[]{ TEXT("안녕 Hello!") };

		std::wstring String{ L"안녕 Hello!" };
		std::wstring String2{ TEXT("안녕 Hello!") };

		if (String == String2)
		{
			std::cout << "Same!\n";
		}

		std::wstring WString = TEXT("Hello World!");
		if (!WString.empty())
		{
			size_t Size = WString.size();
			const size_t FindIndex = WString.find(TEXT("d!"));

			if (FindIndex != std::wstring::npos)
			{
				std::cout << std::format("d! index = {} \n", FindIndex);
				WString.replace(FindIndex, 2, TEXT("@#"));
			}

			const size_t FindIndex2 = WString.find(TEXT("!!!"));
		}
	}
	// 문자열을 다른 자료형으로 변환
	{
		// 문자열을 정수로(string to int: stoi)
		{
			std::wstring StringNumber{ TEXT("20") };
			int Number = std::stoi(StringNumber);
			std::cout << Number << std::endl;
		}
		// 정수를 문자열로
		{
			std::wstring WString = std::to_wstring(1000);
			std::string String = std::to_string(1000);
			//std::string String2 = 1000;
		}
		// 문자열을 유니코드 문자열
		{
			std::string String = "Hello 한글 こんにちは 哈罗 صباح الخير\n";
			// 필요한 경우 해당 함수를 찾아서 사용하면 된다.
			//std::wstring WString = std::wstring(String.begin(), String.end());
		}
		// 정수를 float로
		{
			std::wstring String{ TEXT("2.35f") };
			// String to Float
			float Float = std::stof(String);
			std::wstring String2 = std::to_wstring(Float);
		}
		{
			class FString : public std::wstring
			{
			public:
				int ToInt() const
				{
					return std::stoi(*this);
				}
			};

			FString String{ TEXT("1024") };
			size_t Size = String.size();
			int Int = String.ToInt();
			wchar_t* Data = String.data();
			Data[0] = TEXT('A');
			String[0] = TEXT('B');
		}
	}
#pragma endregion
#pragma region StringView
	{

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
