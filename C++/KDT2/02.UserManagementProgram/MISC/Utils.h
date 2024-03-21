#pragma once

#include "Classes/Account.h"
struct FUtils
{
	static FAccount MakeAccountFromUserInput() {
		FAccount Account;
		cout << "Input ID : \n";
		cin >> Account.ID;

		cout << "Input PassWord : \n";
		cin >> Account.Password;
		return Account;
	}
	// InFunctionName: __FUNCTION__
	static void PrintSystemSuccessOrFailed(bool bFlag, const char* InFunctionName)
	{
		if (bFlag)
		{
			cout << format("[System]{} success\n", InFunctionName);
		}
		else
		{
			cout << format("[System]{} failed\n", InFunctionName);
		}
	}
};

