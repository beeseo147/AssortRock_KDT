#include <iostream>
#include "LaunchEngineLoop.h"

int32 LAUNCH_API GuardedMain(const TCHAR* CmdLine);

atomic_int a_A = 0;

int32 main()
{
    int32 ErrorLevel = GuardedMain(nullptr);

    return ErrorLevel;
}