#pragma once
namespace KDT
{
	int Test()
	{
		return 5;
	}

	template<class T>
	class vector
	{
	public:
		void push_back(const T& InData)
		{
			if (IsFull())
			{
				reserve(Size * 2);
			}

			// Array[Size] = InData;
			new(Array + Size)T(InData);
			++Size;
		}
		void push_back(T&& InData)
		{
			if (IsFull())
			{
				reserve(Size * 2);
			}

			// Array[Size] = InData;
			new(Array + Size)T(std::move(InData));
			++Size;
		}

		void reserve(const size_t InSize)
		{
			const static size_t MinSize = 2;
			// end 위치가 될 공간을 위해 + 1 을 해줬다
			const size_t NewSize = std::max(MinSize, InSize) + 1;

			//T* NewArray = new T[NewSize];
			T* NewArray = (T*)malloc(sizeof(T) * NewSize);

			// 배열이 비어 있지 않은 경우
			if (!empty())
			{
				// 원래 들어있던 데이터를 복사해온다
				for (int i = 0; i < Size; ++i)
				{
					//NewArray[i] = std::move(Array[i]);
					// placement new: 이미 할당된 메모리 공간에 생성자를 호출
					new(NewArray + i)T(std::move(Array[i]));
					// new(&NewArray[i])
					Array[i].~T();
				}
			}

			// 복사 이후 원래 데이터가 들어있던 공간을 해제한다
			if (Array)
			{
				//delete[] Array;
				free(Array);
				Array = nullptr;
			}

			// 신규 할당된 NewArray의 주소를 Array에 전달한다
			Array = NewArray;
			Capacity = NewSize - 1;
		}

		void resize(const size_t InSize)
		{
			reserve(InSize);
			for (size_t i = Size; i < InSize; ++i)
			{
				push_back({});
			}
		}

		void clear()
		{
			if (Array == nullptr) { return; }

			for (int i = 0; i < Size; ++i)
			{
				Array[i].~T();
			}

			//delete[] Array;
			free(Array);
			Array = nullptr;

			Size = 0;
			Capacity = 0;
		}

		_NODISCARD_EMPTY_MEMBER _CONSTEXPR20 bool empty() const
		{
			return Size == 0;
		}

		_NODISCARD size_t size() const { return Size; }
		_NODISCARD size_t capacity() const { return Capacity; }

		_NODISCARD T& operator[](const size_t InIndex) const
		{
			return Array[InIndex];
		}

	public:
		vector() = default;
		~vector()
		{
			clear();
		}

	private:
		_NODISCARD bool IsFull() const
		{
			return Size == Capacity;
		}

	private:
		T* Array = nullptr;
		size_t Size = 0;			// 실제로 할당된 원소의 갯수
		size_t Capacity = 0;		// 할당 가능한 총 원소의 갯수
	};
}