#include "LaunchEngineLoop.h"

FEngineLoop EngineLoop;

/**
 * PreInits the engine loop
 */
int32 EnginePreInit(const TCHAR* CmdLine)
{
	E_Log(trace, "");
	const int32 ErrorLevel = EngineLoop.PreInit(CmdLine);

	return ErrorLevel;
}

/**
 * Inits the engine loop
 */
int32 EngineInit()
{
	E_Log(trace, "");
	const int32 ErrorLevel = EngineLoop.Init();

	return ErrorLevel;
}

/**
 * Ticks the engine loop
 */
void EngineTick()
{
	E_Log(trace, "");
	EngineLoop.Tick();
}

/**
 * Shuts down the engine
 */
void EngineExit()
{
	E_Log(trace, "");
	EngineLoop.Exit();
}

int32 LAUNCH_API GuardedMain(const TCHAR* CmdLine)
{
	int32 ErrorLevel = 0;

	// 초기화
	ErrorLevel = EnginePreInit(CmdLine);
	if (ErrorLevel != 0) { return ErrorLevel; }
	ErrorLevel = EngineInit();
	if (ErrorLevel != 0) { return ErrorLevel; }

	// 시뮬레이션
	EngineTick();

	// 종료
	EngineExit();

	return ErrorLevel;
}