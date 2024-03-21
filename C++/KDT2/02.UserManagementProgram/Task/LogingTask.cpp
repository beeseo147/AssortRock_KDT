#include "LogingTask.h"

FLogingTask::FLogingTask()
{
	cout << "[------    Login      ------]" << endl;
	const FAccount Account = FUtils::MakeAccountFromUserInput();
	pair Result = GLoginSession.Login(Account);
	cout << Result.second << endl;
}
