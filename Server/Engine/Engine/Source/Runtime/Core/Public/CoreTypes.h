#pragma once
#pragma warning(disable: 4251)
#include <string>
#include <format>
#include <memory>
#include <typeinfo>
#include <functional>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Containers --------------
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
// Containers End --------------

#include "UObject/UObjectMacros.h"
#include "HAL/Platform.h"

// Boost --------------------------------------------------------------------
#include <boost/log/trivial.hpp>
#include <boost/pool/pool.hpp>

namespace boost
{
	inline BOOST_NORETURN void throw_exception(std::exception const&) {}
	inline void __cdecl throw_exception(class std::exception const&, struct boost::source_location const&) {}
}
// Boost End ----------------------------------------------------------------

using namespace std;
using FString = wstring;
using FStringView = wstring_view;