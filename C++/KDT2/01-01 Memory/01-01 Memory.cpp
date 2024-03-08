#include <iostream>
#include "Function.h"
// 프로젝트 속성 -> C/C++ -> 일반 -> 추가 포함 디렉토리
// ->$(ProjectDir)Funtion

int GA = 10;

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
	}
}

