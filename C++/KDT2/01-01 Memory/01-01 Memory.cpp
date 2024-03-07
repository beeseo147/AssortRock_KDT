#include <iostream>

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
}

