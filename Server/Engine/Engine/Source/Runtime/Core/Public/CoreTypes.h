#pragma once
#pragma warning(disable: 4251)
#include <string>
#include <format>
#include <memory>
#include <typeinfo>
#include <functional>
#include <codecvt>
#include <filesystem>
#include <chrono>

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
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>

namespace boost
{
	inline BOOST_NORETURN void throw_exception(std::exception const&) {}
	inline void __cdecl throw_exception(class std::exception const&, struct boost::source_location const&) {}
}
// Boost End ----------------------------------------------------------------

using namespace std;
using FString = wstring;
using FStringView = wstring_view;

#include "MISC/Name.h"

//ThirdParty
#include "inicpp.h"
#include "Reflection/meta.hpp"
#include "Reflection/factory.hpp"

using namespace meta;

enum EPropertyType : uint8
{
	T_NONE,
	T_POINTER,
	T_SHARED_PTR,
	T_ENGINE_WEAK_PTR,
	T_WEAK_PTR,
	T_INT,
	T_FLOAT,
};

struct FProperty
{
	EPropertyType PropertyType = EPropertyType::T_NONE;
	string Name;
	FString ClassName;
};