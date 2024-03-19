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
		const size_t MemorySize = BlockSize * MaxCount;

		// 재대로 할려면 얼리인먼트 까지 고려해야 한다
		// 일단은 저희는 연습이니까..
		StartAddress = ::malloc(MemorySize);
		MemoryBlock.reserve(MaxCount);
		for (size_t i = 0; i < MaxCount; ++i)
		{
			MemoryBlock.push_back((uint8_t*)StartAddress + i * BlockSize);
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
			free(StartAddress);
		}
	}

private:
	const size_t BlockSize;
	const size_t MaxCount;
	void* StartAddress = nullptr;
	//std::vector<void*> MemoryBlock;
	boost::container::vector<void*> MemoryBlock;
};