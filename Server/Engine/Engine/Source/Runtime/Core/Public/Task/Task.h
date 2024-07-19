#pragma once
#include "CoreTypes.h"

namespace ENamedThreads
{
	enum Type : int32
	{
		MainThread,
		AnyThread,
	};
}
struct CORE_API FTask
{
	virtual ~FTask() {}
	virtual void ExecuteTask() {}
};
class CORE_API FTaskManager
{
public:
	static FTaskManager* Get(const bool bDestroy = false);

	//들어온 함수를 실행하는
	template<typename TTask, typename... Types>
	void InvokeTask(Types... InArgs)
	{
		static_assert(is_base_of_v<FTask, TTask> InArgs);
		TTask NewTask = TTask(InArgs...);
		NewTask.ExecuteTask();
	}
protected:
	//단발성 Task

};

template<typename TTask, typename... Types>
void InvokeTask(Types &&... InArgs)
{
	FTaskManager::Get()->InvokeTask<TTask>(InArgs...);
}