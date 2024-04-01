#pragma once
#include <iostream>
#include <chrono>
#include <format>
#include <array>
#include <vector>
#include <functional>
#include <boost/container/vector.hpp>

using namespace std;

// 고정 사이즈 Memory pool
class FMemoryPool
{
public:
	FMemoryPool(const size_t InBlockSize,
		const size_t InMaxCount)
		: BlockSize(InBlockSize)
		, MaxCount(InMaxCount)
	{
		const size_t Align = 8;
		const size_t AlignedBlockSize = BlockSize + Align - (BlockSize % Align);
		//const size_t AlignedBlockSize = BlockSize;
		const size_t MemorySize = AlignedBlockSize * MaxCount;

		//StartAddress = ::malloc(MemorySize);
		StartAddress = ::_aligned_malloc(MemorySize, Align);
		MemoryBlock.reserve(MaxCount);
		for (size_t i = 0; i < MaxCount; ++i)
		{
			MemoryBlock.push_back((uint8_t*)StartAddress + i * AlignedBlockSize);
		}
	}

	void* malloc()
	{
		if (MemoryBlock.empty())
		{
			return nullptr;
		}

		void* Pointer = MemoryBlock.back();
		MemoryBlock.pop_back();
		return Pointer;
	}

	void free(void* InMemory)
	{
		MemoryBlock.push_back(InMemory);
	}

	~FMemoryPool()
	{
		if (StartAddress)
		{
			//::free(StartAddress);
			::_aligned_free(StartAddress);
		}
	}

private:
	const size_t BlockSize;
	const size_t MaxCount;
	void* StartAddress = nullptr;
	std::vector<void*> MemoryBlock;
	//boost::container::vector<void*> MemoryBlock;
};

template<class T>
class FObjectPool : public FMemoryPool
{
public:
	FObjectPool(const size_t InMaxObjectCount)
		: FMemoryPool(sizeof(T), InMaxObjectCount)
	{
	}

	template<class... Args>
	T* construct(Args&&... InArgs)
	{
		T* ret = reinterpret_cast<T*>(FMemoryPool::malloc());
		// std::forward: L-Value로 들어왔다면 L-Value로 전달(cast)
		//				 R-Value로 들어왔다면 R-Value로 전달(cast)
		// std::move: R-Value로 전달(cast)
		new(ret)T(std::forward<Args>(InArgs)...);

		return ret;
	}

	template<class... Args>
	std::shared_ptr<T> construct_shared(Args&&... InArgs)
	{
		T* ret = reinterpret_cast<T*>(FMemoryPool::malloc());
		new(ret)T{ std::forward<Args>(InArgs)... };

		return std::shared_ptr<T>{ret, [this](T* InPointer)
			{
				destroy(InPointer);
			}};
	}

	void destroy(T* const chunk)
	{
		chunk->~T();
		FMemoryPool::free(chunk);
	}
};

struct FMemoryHeader
{
	int Flag = 0;
	int Flag2 = 1;
	int Flag3 = 2;
};

class FData
{
public:
	FData()
	{
		FMemoryHeader* Header = GetMemoryHeader();
		cout << "FData\n";
	}
	~FData()
	{
		cout << "~Data\n";
	}

	//FData(FMemoryHeader Header)
	//{

	//}

	FMemoryHeader* GetMemoryHeader()
	{
		FMemoryHeader* Header = reinterpret_cast<FMemoryHeader*>(this) - 1;

		return Header;
	}

protected:
	int Value = 2;
};

class FData2 : public FData
{
public:
	FData2()
	{
		FMemoryHeader* Header = GetMemoryHeader();
		cout << "FData2\n";
	}
	//FData2(FMemoryHeader Header)
	//	: FData(Header)
	//{

	//}
	~FData2()
	{
		cout << "~FData2\n";
	}
};

struct FObjectInitializer
{
	int Flag = 0;
	int Flag2 = 1;
	int Flag3 = 2;
};

class FObjectBase
{
public:
	FObjectBase() {}
	FObjectBase(const FObjectInitializer& InObjectInitializer)
		: Flag(InObjectInitializer.Flag)
		, Flag2(InObjectInitializer.Flag2)
		, Flag3(InObjectInitializer.Flag3)
	{

	}
	virtual ~FObjectBase() {}

protected:
	// 아래는 값을 초기화 하면 안됨
	int Flag;
	int Flag2;
	int Flag3;
};

class FObject : public FObjectBase
{
public:
	template<class T>
	static T* NewObject(const FObjectInitializer& InObjectInitializer)
	{
		// template 안에 있는 static 변수는
		// 각 타입마다 인스턴스가 따로 존재한다
		static FMemoryPool MemoryPool{ sizeof(T), 10 };
		FObjectBase* ObjectBase = (FObjectBase*)MemoryPool.malloc();
		new(ObjectBase) FObjectBase(InObjectInitializer);
		new(ObjectBase) T();
		T* NewObject = (T*)ObjectBase;
		return NewObject;
	}

	FObject()
	{
		Flag;
		Flag2;
		Flag3;
	}
	~FObject()
	{

	}

protected:
	int Value = 2;
private:
};

class FTest : public FObject
{
public:
	FTest()
	{
		if (Flag == 1000)
		{
			cout << "Flag is 1000\n";
		}
	}

	int Test = 1000;
};

template <class _Ty>
class FAllocator
{
public:
	static inline shared_ptr<boost::pool<>> Pool;
	friend class std::_Ref_count_obj_alloc3<_Ty, FAllocator<_Ty>>;
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
	FAllocator() noexcept {}
	constexpr FAllocator(const FAllocator&) noexcept = default;
	template <class _Other>
	constexpr FAllocator(const FAllocator<_Other>& InOther) noexcept
	{
		if (!Pool)
		{
			auto& Type = typeid(_Other);
			const char* Test = Type.name();
			Pool = make_shared<boost::pool<>>(sizeof(_Other), 100000);
			Pool->free(Pool->malloc());
		}
	}
	_CONSTEXPR20 ~FAllocator() = default;
	_CONSTEXPR20 FAllocator& operator=(const FAllocator&) = default;

	_CONSTEXPR20 void deallocate(_Ty* const _Ptr, const size_t _Count) {
		_STL_ASSERT(_Ptr != nullptr || _Count == 0, "null pointer cannot point to a block of non-zero size");
		_STL_ASSERT(_Count == 1, "error");
		// no overflow check on the following multiply; we assume _Allocate did that check
		//_Deallocate<_New_alignof<_Ty>>(_Ptr, sizeof(_Ty) * _Count);
		Pool->free(_Ptr);
	}

	_NODISCARD_RAW_PTR_ALLOC _CONSTEXPR20 __declspec(allocator) _Ty* allocate(_CRT_GUARDOVERFLOW const size_t _Count) {
		static_assert(sizeof(value_type) > 0, "value_type must be complete before calling allocate.");
		//return static_cast<_Ty*>(_Allocate<_New_alignof<_Ty>>(_Get_size_of_n<sizeof(_Ty)>(_Count)));
		//return reinterpret_cast<_Ty*>(Pool->construct());
		return (_Ty*)Pool->malloc();
	}
};

_EXPORT_STD template <class _Ty, class _Other>
_NODISCARD _CONSTEXPR20 bool operator==(const FAllocator<_Ty>&, const FAllocator<_Other>&) noexcept {
	return true;
}
_EXPORT_STD template <class _Ty, class _Other>
_NODISCARD _CONSTEXPR20 bool operator!=(const FAllocator<_Ty>& a, const FAllocator<_Other>& b) noexcept {
	return !(a == b);
}