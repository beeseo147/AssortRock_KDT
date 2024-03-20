// 01-10.Pool.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pool.h"
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>

class FClass
{
public:
	FClass()
	{
		cout << __FUNCTION__ << endl;
	}
	~FClass()
	{
		cout << __FUNCTION__ << endl;
	}
};

int main()
{
	// new
	{
		FClass* Class = new FClass;
		delete Class;
	}
	// malloc
	{
		FClass* Class = (FClass*)malloc(sizeof(FClass));
		// placement new: 이미 할당된 메모리 블록에
		// 객체(인스턴스)를 만들어준다(생성자 호출)
		new(Class)FClass();
		Class->~FClass();
		free(Class);
	}

	// 메모리풀: 큰 사이즈의 메모리 블록을 할당하고
	// 요청할때 마다 미리 할당해둔 블록의 일부를 전달한다
	// 요청이 만료되면 다시 풀에 환원된다

	// 메모리 할당이란: 커널에 요청하는 명령(system call)중 하나이다
	// (OS가 최적화를 해놔서 매번 커널에 요청하는 것은 아닐 수도 있다)
	// 왜 커널에 요청하는가? 메모리는 공유 자산(내 프로그램만 쓰는 것이 아니다)
	// 이러한 공유자원을 사용하는 요청은(시스템 콜 중 하나) 동기화 처리가
	// 되어야 할 것이다.(여러 프로그램이 동시에 요청할때 하나씩만 처리되어야 함)

	// 위와 같은 상황의 경우 최대한 커널 영역에 있는 시간을 줄여야 (OS입장에서는)
	// 프로그램이 더 빠르게 동작한다고 할 수 있겠습니다.
	// 메모리 할당 및 해제를 빈번하게 하는 경우 메모리 풀을 만들어서 사용하면
	// 커널에 있는 시간을 많이 줄일 수 있다.

	// 메모리 풀을 사용했을 때 장점
	// - 속도가 빠르다(구현을 못하면 더 느리다; 어중간하게 구현하면 new delete하는 것 만 못하다)
	//		-> 결국 만들고 성능을 측정해야 한다
	//		- 미리 적은 횟수의 시스템 콜로 메모리 블록을 할당하고 그것을 유저영역에서 사용하기 때문에
	//		- (메모리 단편화 문제 해결)큰 블록을 할당해두고 이를 유저가 쪼개서 사용하기 때문에
	//        캐시 미스가 적다
	// 고정 사이즈 메모리 풀
	//		- 예산(메모리)을 정해서 그 예산 안에서 사용하게 제한할 수 있다
	//			- 예를 들면 메모리풀 크기를 10으로 고정해두고 이를 사용하면 최대 동시에 10개까지 (인스턴스)만들수 있다

	const size_t MaxCount = 1000000;
	{
		auto Start{ std::chrono::steady_clock::now() };
		{
			for (size_t i = 0; i < MaxCount; ++i)
			{
				int* Test = new int[1024];
				delete[] Test;
			}
		}
		auto End{ std::chrono::steady_clock::now() };
		auto Diff{ End - Start };
		// 1000ms == 1sec
		std::cout << std::format("new[], delete[]: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
	}
	{
		auto Start{ std::chrono::steady_clock::now() };
		{
			for (size_t i = 0; i < MaxCount; ++i)
			{
				int* Test = new int;
				delete Test;
			}
		}
		auto End{ std::chrono::steady_clock::now() };
		auto Diff{ End - Start };
		// 1000ms == 1sec
		std::cout << std::format("new, delete: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
	}
	{
		//FMemoryPool MemoryPool{ sizeof(int) /** 1024*/, MaxCount };
		FMemoryPool MemoryPool{ 4, MaxCount };
		auto Start{ std::chrono::steady_clock::now() };
		{
			for (size_t i = 0; i < MaxCount; ++i)
			{
				char* Test = (char*)MemoryPool.malloc();
				*Test = (char)i;
				//MemoryPool.free(Test);
			}
		}
		auto End{ std::chrono::steady_clock::now() };
		auto Diff{ End - Start };
		std::cout << std::format("FMemoryPool: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
	}
	{
		boost::pool<> Pool(sizeof(int), MaxCount); // 100000: 최초 할당시 확보할 item의 갯수(1024*100000 의 메모리가 할당된다)
		int* TryAlloc = (int*)Pool.malloc();	// 1회 호출해서 메모리를 할당한다
		Pool.free(TryAlloc);

		auto Start{ std::chrono::steady_clock::now() };
		{
			for (size_t i = 0; i < MaxCount; ++i)
			{
				int* Test = (int*)Pool.malloc();
				//*Test = i;
				//Pool.free(Test);
			}
		}
		auto End{ std::chrono::steady_clock::now() };
		auto Diff{ End - Start };
		std::cout << std::format("boost::pool: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
	}

	// 오브젝트 풀: 메모리풀은 순수한 메모리 블락만 가지고 있고, 오브젝트 풀은
	// placement new를 사용해서 Object를 만들어주는 기능이 추가됨
	{
		struct FData
		{
		public:
			FData()
			{
				//std::cout << __FUNCTION__ << std::endl;
			}
			FData(const int InA, const int InB)
			{

			}
			~FData()
			{
				//std::cout << __FUNCTION__ << std::endl;
			}

			int Value = 10;
			int Value2 = 10;
		};

		{
			auto Start{ std::chrono::steady_clock::now() };
			{
				for (size_t i = 0; i < MaxCount; ++i)
				{
					FData* Data2 = new FData((int)i, 20);
					delete Data2;
				}
			}
			auto End{ std::chrono::steady_clock::now() };
			auto Diff{ End - Start };
			std::cout << std::format("new FData: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
		}
		{
			boost::object_pool<FData> ObjectPool{ MaxCount };
			ObjectPool.free(ObjectPool.malloc());

			auto Start{ std::chrono::steady_clock::now() };
			{
				for (size_t i = 0; i < MaxCount; ++i)
				{
					FData* Data2 = ObjectPool.construct();
					ObjectPool.destroy(Data2);
				}
			}
			auto End{ std::chrono::steady_clock::now() };
			auto Diff{ End - Start };
			std::cout << std::format("boost::object_pool: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
		}

		{
			boost::object_pool<FData> ObjectPool{ MaxCount };
			ObjectPool.free(ObjectPool.malloc());

			auto Start{ std::chrono::steady_clock::now() };
			{
				for (size_t i = 0; i < MaxCount; ++i)
				{
					FData* Data2 = ObjectPool.construct();
					std::shared_ptr<FData> SmartPointer{ Data2, [&ObjectPool](FData* InPointer)
						{
							ObjectPool.destroy(InPointer);
						} };
					//ObjectPool.destroy(Data2);
				}
			}
			auto End{ std::chrono::steady_clock::now() };
			auto Diff{ End - Start };
			std::cout << std::format("boost::object_pool shared_ptr: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
		}
		{
			FObjectPool<FData> ObjectPool{ MaxCount };

			auto Start{ std::chrono::steady_clock::now() };
			{
				for (size_t i = 0; i < MaxCount; ++i)
				{
					FData* Data2 = ObjectPool.construct((int)i, 10);
					ObjectPool.destroy(Data2);
				}
			}
			auto End{ std::chrono::steady_clock::now() };
			auto Diff{ End - Start };
			std::cout << std::format("FObjectPool: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
		}
		{
			FObjectPool<FData> ObjectPool{ MaxCount };

			auto Start{ std::chrono::steady_clock::now() };
			//std::shared_ptr<FData> Test;
			{
				for (size_t i = 0; i < MaxCount; ++i)
				{
					std::shared_ptr<FData> Data2 = ObjectPool.construct_shared((int)i, 10);
					/*if (i == 0)
					{
						Test = Data2;
					}*/
				}
			}
			auto End{ std::chrono::steady_clock::now() };
			auto Diff{ End - Start };
			std::cout << std::format("FObjectPool construct_shared: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
		}
		{
			auto Start{ std::chrono::steady_clock::now() };
			//std::shared_ptr<FData> Test;
			{
				for (size_t i = 0; i < MaxCount; ++i)
				{
					std::shared_ptr<FData> Data2 = std::make_shared<FData>((int)i, 10);
				}
			}
			auto End{ std::chrono::steady_clock::now() };
			auto Diff{ End - Start };
			std::cout << std::format("shared_ptr<FData>: {}ms\n", std::chrono::duration<double, std::milli>(Diff).count());
		}
	}
	// Memory Header
	{
		//  r(MemoryHeader)		 r(12byte), FData*
		//  [                    |                            ]
		FMemoryPool MemoryPool{ sizeof(FMemoryHeader) + sizeof(FData), 1 };
		void* Pointer = MemoryPool.malloc();
		FMemoryHeader* Header = static_cast<FMemoryHeader*>(Pointer);
		new(Header)FMemoryHeader();
		Header->Flag = 999;

		FData2* Data = reinterpret_cast<FData2*>(Header + 1);
		new(Data)FData2();
	}
	// Unreal 스타일
	{
		FObjectInitializer Init;
		Init.Flag = 1234;
		FObject* Object = FObject::NewObject<FObject>(Init);
		FTest* Object2 = FObject::NewObject<FTest>(Init);
		Init.Flag = 1000;
		FTest* Object3 = FObject::NewObject<FTest>(Init);
	}
}