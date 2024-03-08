#include <iostream>
#include "Function.h"
#include<unordered_map>
#include<functional>

// 프로젝트 속성 -> C/C++ -> 일반 -> 추가 포함 디렉토리
// ->$(ProjectDir)Funtion
//KIM

int GA = 10;
std::shared_ptr<FStruct> GSharedPtrStruct;
std::weak_ptr<FStruct> GWeakPtrStruct;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(72);

	// Stack memory
	{
		int i1{ 1 };
		int i2{ 2 };
		int i3{ 3 };
		// Stack						// Heap
		// [4byte]i1{1}
		// [4byte]i2{2}
		// [4byte]i3{3}

		i1 = 10;
		// Stack						// Heap
		// [4byte]i1{10}
		// [4byte]i2{2}
		// [4byte]i3{3}
	}

	// Pointer, 동적 할당
	{
		// 64bit 기준
		int* Pointer{ nullptr };
		// Stack						// Heap
		// [8byte]Pointer{nullptr(0)}

		Pointer = new int{ 444 };
		// Stack							// Heap
		// [8byte]Pointer{0xHeapAddress} ---> [4byte]*Pointer{444}

		*Pointer = 555;
		// Stack							// Heap
		// [8byte]Pointer{0xHeapAddress} ---> [4byte]*Pointer{555}

		delete Pointer;
		// Stack							// Heap
		// Debug 모드에서는 delete 하는 경우 친절하게 삭제한 영역이라는 의미로
		// 0x0000000000008123로 바꿔준다
		// [8byte]Pointer{0x0000000000008123} ---> x

		Pointer = nullptr;
		// Stack							// Heap
		// [8byte]Pointer{nullptr(0)}
	}
	// Pointer, 지역 변수
	{
		int A = 0;
		int* Pointer = &A;
		// Stack									// Heap
		// [4byte]A{0}
		// [4byte]padding memory
		// [8byte]Pointer{A StackMemoryAddress}

		A = 100;
		// Stack									// Heap
		// [4byte]A{0 -> 100}
		// [4byte]padding memory
		// [8byte]Pointer{A StackMemoryAddress}
		*Pointer = 1000;
		// Stack									// Heap
		// [4byte]A{100 -> 1000}
		// [4byte]padding memory
		// [8byte]Pointer{A StackMemoryAddress}
	}
	// Pointer, 전역 변수
	{
		int* Pointer = &GA;
		// Stack									// Data
		// [8byte]Pointer{GA DataMemoryAddress}		[4byte]GA{10}
		*Pointer = 1000;
		// Stack									// Data
		// [8byte]Pointer{GA DataMemoryAddress}		[4byte]GA{10->1000}
	}
	// Double Pointer, 동적할당
	{
		int** DoublePointer{ nullptr };
		// Stack									// Heap
		// [8byte]DoublePointer{nullptr}

		DoublePointer = new int*;
		// Stack									// Heap
		// [8byte]DoublePointer{0xHeapAddress} --->  [8byte]*DoublePointer{trash (0xcdcdcdcdcdcdcdcd)}

		*DoublePointer = new int{ 10 };
		// Stack									// Heap
		// [8byte]DoublePointer{0xHeapAddress} --->  [8byte]*DoublePointer{0xHeapAddress}
		//											 -> [4byte]**DoublePointer{10}

		**DoublePointer = 100;
		// Stack									// Heap
		// [8byte]DoublePointer{0xHeapAddress} --->  [8byte]*DoublePointer{0xHeapAddress}
		//											 -> [4byte]**DoublePointer{100}

		delete* DoublePointer;
		// Stack									// Heap
		// [8byte]DoublePointer{0xHeapAddress} --->  [8byte]*DoublePointer{0xHeapAddress}
		//											 -> x

		delete DoublePointer;
		// Stack									// Heap
		// [8byte]DoublePointer{0xHeapAddress} --->  x

		DoublePointer = nullptr;
		// Stack									// Heap
		// [8byte]DoublePointer{nullptr}
	}
	// Double pointer tip (COM; Component Object Model 공부 해보시면 도움이 될 것 같습니다)
	{
		// Wrong case
		{
			int* Pointer = nullptr;
			int* Pointer2 = nullptr;
			// Stack									// Heap
			// [8byte]Pointer{nullptr}
			// [8byte]Pointer2{nullptr}
			//AllocateWrong(Pointer, Pointer2);

			//int* InTarget1 = Pointer;
			////int* InTarget1 = nullptr;
			//int* InTarget2 = Pointer2;
			////int* InTarget2 = nullptr;
			//// Stack									// Heap
			//// [8byte]Pointer{nullptr}
			//// [8byte]Pointer2{nullptr}
			//// [8byte]InTarget1{nullptr}		[4byte]*InTarget1{trash}
			//// [8byte]InTarget2{nullptr}		[4byte]*InTarget2{trash}
			//InTarget1 = new int;
			//InTarget2 = new int;
		}
		// Correct case
		{
			int* Pointer = nullptr;
			int* Pointer2 = nullptr;
			// Stack									// Heap
			// [8byte]Pointer{nullptr}
			// [8byte]Pointer2{nullptr}
			AllocateCorrect(&Pointer, &Pointer2);
			//int** InTarget1 = &Pointer;
			////int** InTarget1 = Pointer의 주소;
			//int** InTarget2 = &Pointer2;
			////int* InTarget2 = Pointer2의 주소;

			//*InTarget1 = new int{ 10 };
			//// Stack									// Heap
			//// [8byte]Pointer{HeapMemoryAddress}	<-----ㄱ
			//// [8byte]InTarget1{&Pointer}				[4byte]*InTarget1->Pointer{}
			//**InTarget1 = 100;

			//delete Pointer;
			Delete(Pointer);
			Delete(Pointer2);
		}
	}
	// 메모리 누수 (Memory leak)
	{
		// Stack					// Heap
		//							?{0xAddress}
		new int;
	}

	// 배열과 메모리 할당
	{
		// 배열
		{
			int Array[5]{ 3,4,5,/*0, 0*/ };
			// Stack						// Heap
			// Array[0]{3}
			// Array[1]{4}
			// Array[2]{5}
			// Array[3]{0}
			// Array[4]{0}
		}
		// 배열 동적 할당
		{
			int* Pointer = new int[5]; /* { 3, 4, 5, 0, 0 };*/
			for (int i = 0; i < 5; ++i)
			{
				// 두가지 방법으로 접근 가능!
				Pointer[i] = i;
				*(Pointer + i) = i + 1;
			}
			// Stack								// Heap
			// [8byte]Pointer{HeapMemoryAddress}	Pointer[0]{0}	=> *(Pointer + 0){1}
			//										Pointer[1]{1}	=> *(Pointer + 1){2}
			//										Pointer[2]{2}	=> *(Pointer + 2){3}
			//										Pointer[3]{3}	=> *(Pointer + 3){4}
			//										Pointer[4]{4}	=> *(Pointer + 4){5}
			delete[] Pointer;
			Pointer = nullptr;
		}
		// 2차원 배열
		{
			char Array[3][2]{};
			for (int i = 0; i < 3; ++i)
			{
				for (int k = 0; k < 2; ++k)
				{
					Array[i][k] = char(i * 2 + k);
				}
			}
			// Stack					// Heap
			// Array[0][0]{0}
			// Array[0][1]{1}
			// Array[1][0]{2}
			// Array[1][1]{3}
			// Array[2][0]{4}
			// Array[2][1]{5}
		}
		// 다차원 배열 동적할당 쓰지말자
		{
		}
		// 함수에 포인터로 배열 전달
		{
			int Array[100]{};
			InitArray(Array, 100);

			int Array2[500]{};
			InitArray(Array2, 500);
		}
		// STL(Standard Template Library)에 있는 자료구조
		{
			std::vector<int> Vector;
			Vector.resize(10);

			/*for (int i = 0; i < 10; ++i)
			{
				Vector[i] = i;
			}*/
			InitArray(Vector);
			InitArray(&Vector);
		}
		// Sum
		{
			int Result = 888;
			std::vector<int> Numbers{ 1,2,3,4,5,6 };
			Sum(Numbers, &Result);
		}
		// Swap
		{
			int A = 10;
			int B = 560;
			Swap(A, B);
		}
	}

	// Smart Pointer
	{
		using namespace std;

		// unique_ptr
		{
			// 단 하나의 동적할당된 인스턴스만 동시에 존재할 수 있다
			unique_ptr<int> Unique = make_unique<int>(10);
			*Unique = 1000;
		}
		// 커스텀 제거자(딜리터)
		{
			unique_ptr<int, decltype(&CustomDeleterInt)> Unique(new int, CustomDeleterInt);
		}
		{
			unique_ptr<FStruct> Unique = make_unique<FStruct>();
			Unique->Hello();
			UniqueParam(Unique);
			UniqueParam(&Unique);
			UniqueParam(Unique.get());


			shared_ptr<FStruct> Unique2 = make_shared<FStruct>();
			UniqueParam(Unique2.get());
		}

		//shared_ptr
		{
			shared_ptr<int> SharedPtr{ make_shared<int>(100) };
			*SharedPtr = 1000;

			shared_ptr<FStruct> SharedPtrStruct{ make_shared<FStruct>() };
			shared_ptr<FStruct> SharedPtrStruct2{ make_shared<FStruct>(999) };
			shared_ptr<FStruct> SharedPtrStruct3{ make_shared<FStruct>(1000.f) };

			int Count = SharedPtrStruct.use_count();
			GSharedPtrStruct = SharedPtrStruct;
			Count = SharedPtrStruct.use_count();

			GWeakPtrStruct = SharedPtrStruct;
			Count = SharedPtrStruct.use_count();

			SharedParam(SharedPtrStruct);
			UniqueParam(SharedPtrStruct.get());

			{
				shared_ptr<int> SharedPtrInt{ new int, CustomDeleterInt };
			}
		}
		int Count = GSharedPtrStruct.use_count();
		FStruct* Pointer = GSharedPtrStruct.get();
		
		shared_ptr<FStruct> PointerToSharedPointer = Pointer->shared_from_this();
		weak_ptr<FStruct> PointerToWeakPointer = Pointer->weak_from_this();
		if(!PointerToWeakPointer.expired())
		{
			std::cout << "Pointer가 살아있다\n";
			GWeakPtrStruct.lock()->Hello();
		}
		else
		{
			std::cout << "소멸됨\n";
		}
	}
#pragma region auto
	{
		//컴파일러가 타입을 추론할 수 있는 경우 타입을 추론해주는 기능
		//컴파일러가 타입을 추론해야 하기 때문에 컴파일 시간이 늘어가는 단점
		//(전체 빌드시간 늘어남)

		int a = 10;
		auto aa =10;
		auto Double = 3.0;
		auto Float = 3.5f;

		auto bResult = ReturnTrue();
		int Int = 200;
		auto Pointer = &Int; //자동으로 int*로 해석
		auto* Pointer2 = &Int;//아래처럼 포인터 티를 내주자
		auto& IntReference = Int; //int&

		std::vector<int> Vector{};
		Vector.resize(10);
		for (int& i : Vector) {
			i = 1000;
		}
		for (auto i : Vector) {
			i = 2000;
		}
		for (auto &i : Vector) {
			i = 3000;
		}
		std::unordered_map<int, int> Map;
		for (std::pair<int, int> it : Map) {

		}
		for (auto it : Map) {

		}
	}
#pragma endregion
#pragma region 함수포인터(Function Pointer)
	{
		// 함수도 주소가 부여되어 있다.
		// C++에서는 함수의 주소를 구해서 변수처럼 사용할 수 있다.
		{
			//						리턴타입(함수라는의미)(입력타입)
			using FFunctionPointer = bool(*)();
			bool(*Test)() = ReturnTrue;
			FFunctionPointer Test2 = ReturnTrue;

			bool bResult = Test2();
			bool bResult2 = Test2();

			Test2 = ReturnFalse;
			bool bReult3 = Test2();
		}
		{
			auto Function = ReturnFalse;
			Function();

			Function = ReturnTrue;
			Function;
		}
		{
			std::function<bool()> Function = ReturnTrue;
			std::function Function2 = ReturnFalse;
			Function();
			Function2();
		}
		{
			std::function Function = SumFunction;
			int Result = Function(10, 20);
		}
		{
			auto Function = SumFunction;
			int result = Function(10, 30);
		}
		{
			FStruct Instance;
			FStruct Instance2;
			Instance.SetValue(100);
			Instance2.Hello();
			auto Function = std::bind(&FStruct::Hello, &Instance);
			Function();
			Function = std::bind(&FStruct::Hello, &Instance2);
			Function();

			std::function<void()>Function2 = std::bind(&FStruct::Hello, &Instance);

			//멤버 함수의 경우
			//입력 인자가 있는 경우 std::placeholders::_1,std::placeholders::_2..
			//인자의 갯수 만큼 뒤에 추가로 붙혀 주어야한다.
			auto SetFunction = std::bind(&FStruct::SetValue, &Instance2, std::placeholders::_1);
			SetFunction(10);
		}
	}
#pragma endregion
#pragma region 람다(Lamda)
	{
		[]()
			{
				std::cout << "Lamda Function\n";
			};

		[]()
			{
				std::cout << "Lamda Function\n";
			};
		{
			std::function Lamda = []() {
				std::cout << "Lamda Function\n";
				};
			Lamda();
		}
		{
			std::function Lambda = [](const int InValue)
				{
					std::cout << "Lambda Function\n";
					std::cout << InValue << std::endl;
				};
			Lambda(10);
			Lambda(20);
		}
		{
			std::function Lambda = [](const int InValue)->int
				{
					std::cout << "Lambda Function\n";
					std::cout << InValue << std::endl;
					return InValue;
				};
			int Value = Lambda(10);
		}
		{
			int a = 10, b = 20, c = 30;
			//[]안에 외부 변수를 넣으면 해당 변수를 capture해서
			//함수 내부에서 사용간으하다
			//[a]와 같이 사용하는 경우 a를 값으로 capture한다
			std::function Lambda = [a,b,&c](const int InValue)->int
				{
					std::cout << "Lambda Function\n";
					std::cout << InValue << std::endl;
					std::cout << a << std::endl;
					std::cout << b << std::endl;
					std::cout << c << std::endl;
					c += 100;
					std::cout << c << std::endl;

					return InValue + 100;
				};
			int Value = Lambda(10);
			int Value2 = Lambda(20);
		}
		int cccc = 1000;
		{
			int a = 10, b = 20, c = 30;
			// [=]을 사용하면 현재 캡쳐 가능한 변수를 값으로 캡쳐 해온다
			// , 로 특정 변수만 다르게 처리 할 수 도 있다
			std::function Lambda = [=, &c, &b](const int InValue) -> int
				{
					std::cout << "Lambda Function!\n";
					std::cout << InValue << std::endl;
					std::cout << a << std::endl;
					// a = 100; // 값으로 capture하면 해당 값을 수정할 수 없다

					std::cout << b << std::endl;
					std::cout << c << std::endl;
					c += 100;
					std::cout << c << std::endl;
					std::cout << cccc << std::endl;

					return InValue + 100;
				};
			int Value = Lambda(10);
			int Value2 = Lambda(50);
		}
		{
			int a = 10, b = 20, c = 30;
			// [&]을 사용하면 현재 캡쳐 가능한 변수를 Reference로 캡쳐 해온다
			// , 로 특정 변수만 다르게 처리 할 수 도 있다
			std::function Lambda = [&, a](const int InValue) -> int
				{
					std::cout << "Lambda Function!\n";
					std::cout << InValue << std::endl;
					std::cout << a << std::endl;
					// a = 100; // 값으로 capture하면 해당 값을 수정할 수 없다

					std::cout << b << std::endl;
					std::cout << c << std::endl;
					c += 100;
					std::cout << c << std::endl;
					std::cout << cccc << std::endl;

					return InValue + 100;
				};
			int Value = Lambda(10);
			int Value2 = Lambda(50);
		}
		{
			FunctionFunction(Test);

			FunctionFunction([]() {
				for (int i = 0; i < 10; ++i)
				{
					std::cout << std::format("Lambda!! {}\n", i);
				}
				});

			int a = 100;
			FunctionFunction([&a]() {
				for (int i = 0; i < 10; ++i)
				{
					a += i;
					std::cout << std::format("Lambda!! {} {}\n", a, i);
				}
				});

			// 만약에 등록해둔 람다의 함수가 늦게 호출되는 경우
			// 늦게라는 의미는 아래처럼 즉시 함수호출후 람다가 실행되는 경ㄴ우가 아닌 상황을 의미한다
			// Ex. 멀티스레딩, 엔진에서 다른 시점에 호출되는 경우
			// 람다로 &나 pointer로 capture해둔 변수에 접근하는 경우 해당 변수가 유효한지 확인을 해야 합니다.
			// 그렇지 않은 경우 잠재적인 문제가 발생할 수 있습니다.
			// 쉽게 생각하면 댕글링 포인ㅇ터와 비슷한 이슈라고 할 수 있습니다.
			std::shared_ptr<int> SharedPointer2;
			{
				std::shared_ptr<int> Test = std::make_shared<int>(999);
				std::shared_ptr<int> SharedPointer{ new int, [&Test](int* InPointer)
					{
						// Test는 아래 시점에서 delete 됩니다.
						// 소멸된 주소에 접근해서 잠재적인 문제를 유발할 수 있습니다.
						*Test = 1000;
						std::cout << *Test << std::endl;
						delete InPointer;
					}
				};

				SharedPointer2 = SharedPointer;
			} // <- Test가 사라지는 시점
		}
	}
#pragma endregion
#pragma region Random,sort
	{
		//컴퓨터에서 random함수는 진짜 random이 아닐 수 있습니다.
		//좋은 random 함수를 사용해야 더 random에 가깝다.

		std::random_device RD;
		std::mt19937 Gen(RD());
		std::uniform_int_distribution<int> Dist(0, 999);
		int RandomValue = Dist(Gen);

		std::vector<int> Vector;
		Vector.resize(100);
		for (int& i : Vector) {
			i = Dist(Gen);
		}

		// 오름차순 정렬
		std::sort(Vector.begin(), Vector.end(), std::less<int>{});

		// 내림차순 정렬
		std::sort(Vector.begin(), Vector.end(), std::greater<int>{});
		
		
	}
#pragma endregion
}

