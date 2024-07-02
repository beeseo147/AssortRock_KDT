#pragma once
#include "CoreTypes.h"
#include "UObjectGlobals.h"

struct FMemoryPool
{
public:
    void Create(const string_view InTypeName,const uint64 InSizePerOne);
    void* Malloc();
    void Free(void* InAddress);
    void Destroy();
private:
    string_view TypeName;
    uint64 SizePerOne;
    boost::pool<>* Pool = nullptr;
};

class CORE_API FUObjectArray
{
public:
    void Create(const type_info& InTypeInfo,const uint64 InSizePerOne);
    void* Malloc(const type_info& InTypeInfo);
    void Free(const type_info& InTypeInfo,void* InAdress);
    void Destroy();
private:
    unordered_map<HashKey,FMemoryPool> MapMemoryPool;
};

extern CORE_API FUObjectArray GUObjectArray;

#include "UObject.h"
template <class _Ty>
class FAllocator
{
public:
	static_assert(!is_const_v<_Ty>, "The C++ Standard forbids containers of const elements "
		"because allocator<const T> is ill-formed.");
	static_assert(!is_function_v<_Ty>, "The C++ Standard forbids allocators for function elements "
		"because of [allocator.requirements].");
	static_assert(!is_reference_v<_Ty>, "The C++ Standard forbids allocators for reference elements "
		"because of [allocator.requirements].");

	using _From_primary = FAllocator;

	using value_type = _Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using propagate_on_container_move_assignment = true_type;
	using is_always_equal _CXX20_DEPRECATE_IS_ALWAYS_EQUAL = true_type;
	FAllocator(FObjectInitializer* InObjectInitializer) noexcept :
		Data(InObjectInitializer)
	{
	}
	constexpr FAllocator(const FAllocator&) noexcept = default;
	template <class _Other>
	constexpr FAllocator(const FAllocator<_Other>& InOther) noexcept
		: Data(InOther.Data.ObjectInitializer)
	{
	}
	_CONSTEXPR20 ~FAllocator() = default;
	_CONSTEXPR20 FAllocator& operator=(const FAllocator&) = default;
	//1. allocate -> 클래스에 대한 시작 주소 
	//2. construct-> 실제 클래스 생성과 주소
	//3. 
	_NODISCARD_RAW_PTR_ALLOC _CONSTEXPR20 __declspec(allocator) _Ty* allocate(_CRT_GUARDOVERFLOW const size_t /*_Count*/) {
		static_assert(sizeof(value_type) > 0, "value_type must be complete before calling allocate.");
		_Ty* Pointer = (_Ty*)GUObjectArray.Malloc(Data.ObjectInitializer->Class->ClassTypeInfo);
		return Pointer; 
	}

	template <class _Objty, class... _Types>
	_CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS void construct(_Objty* const _Ptr, _Types&&... _Args)
	{
		Data.ObjectInitializer->Obj = _Ptr;
		new(Data.ObjectInitializer->GetObj())UObjectBase(Data.ObjectInitializer->Class,
			Data.ObjectInitializer->ObjectFlags, Data.ObjectInitializer->OuterPrivate, Data.ObjectInitializer->Name);
		_Objty::__DefaultConstructor(*Data.ObjectInitializer);
	}

	template< class U >
	_CONSTEXPR20 void destroy(U* p)
	{
		UClass* Class = p->GetClass();
		Data.DestructorClass = Class;
		_ASSERT(Class);
		p->~U(); 
	}
	_CONSTEXPR20 void deallocate(_Ty* const _Ptr, const size_t _Count) {
		_STL_ASSERT(_Ptr != nullptr || _Count == 0, "null pointer cannot point to a block of non-zero size");
		_STL_ASSERT(_Count == 1, "error");
		
		GUObjectArray.Free(Data.DestructorClass->ClassTypeInfo, _Ptr);
	}

public:
	union FData
	{
		FObjectInitializer* ObjectInitializer;
		UClass* DestructorClass;
	};
	FData Data;
};

_EXPORT_STD template <class _Ty, class _Other>
_NODISCARD _CONSTEXPR20 bool operator==(const FAllocator<_Ty>&, const FAllocator<_Other>&) noexcept {
	return true;
}
_EXPORT_STD template <class _Ty, class _Other>
_NODISCARD _CONSTEXPR20 bool operator!=(const FAllocator<_Ty>& a, const FAllocator<_Other>& b) noexcept {
	return !(a == b);
}