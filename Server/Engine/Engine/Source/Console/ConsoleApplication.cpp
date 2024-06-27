#include <iostream>
#include "LaunchEngineLoop.h"

int32 LAUNCH_API GuardedMain(const TCHAR* CmdLine);

int32 main()
{
    int32 ErrorLevel = GuardedMain(nullptr);

    return ErrorLevel;
}