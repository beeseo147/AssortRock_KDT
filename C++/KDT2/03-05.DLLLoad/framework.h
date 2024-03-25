#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>
#ifdef MY_DLLLOAD
#define MY_DLLLOAD_API __declspec(dllexport)
#else
#define MY_DLLLOAD_API __declspec(dllimport)
#endif

// 맹글링을 하지 않겠다

extern "C" {
	extern "C" void MY_DLLLOAD_API fnMy0305DLL(int** InPointer);
	void MY_DLLLOAD_API fnMy0305DLLFree(int** InPointer);
}
