#pragma once
#include"MISC/Headers.h"

class FEngine
{
public:
	void Run();

private:
	void Init();
	void Release();
	EMenuEvent PrintMenu();
	
public:
	bool bTerminated = false;
};
inline FEngine GEngine;