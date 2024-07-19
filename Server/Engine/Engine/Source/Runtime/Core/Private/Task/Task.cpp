#include <Task/Task.h>

FTaskManager* FTaskManager::Get(const bool bDestroy)
{
	static unique_ptr<FTaskManager> Instance = make_unique<FTaskManager>();
	if (bDestroy)
	{
		Instance.release();
		return nullptr;
	}

	return Instance.get();
}
