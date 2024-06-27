#pragma once
#include "Public/GenericPlatform/GenericPlatform.h"

/**
* Windows specific types
**/
struct FWindowsPlatformTypes : public FGenericPlatformTypes
{
#ifdef _WIN64
	typedef unsigned __int64	SIZE_T;
	typedef __int64				SSIZE_T;
#else
	typedef unsigned long		SIZE_T;
	typedef long				SSIZE_T;
#endif

#if USE_UTF8_TCHARS
	typedef UTF8CHAR TCHAR;
#endif
};

typedef FWindowsPlatformTypes FPlatformTypes;

// DLL export and import definitions
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)