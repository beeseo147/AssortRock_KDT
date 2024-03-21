#include "DeleteAccountTask.h"
#include "MISC/Utils.h"
#include "Classes/DataBase.h"

FDeleteAccountTask::FDeleteAccountTask()
{
	cout << "[------ Delete Account -----]" << endl;
	FAccount Account = FUtils::MakeAccountFromUserInput();
	bool bResult = GDataBase.DeleteAccount(Account);
	FUtils::PrintSystemSuccessOrFailed(bResult, __FUNCTION__);
}
