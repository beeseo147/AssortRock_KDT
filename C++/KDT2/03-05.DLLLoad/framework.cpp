#include "pch.h"

void MY_DLLLOAD_API fnMy0305DLL(int** InPointer)
{
    std::cout << __FUNCTION__ << std::endl;
}

void MY_DLLLOAD_API fnMy0305DLLFree(int** InPointer)
{
    std::cout << __FUNCTION__ << std::endl;
}
