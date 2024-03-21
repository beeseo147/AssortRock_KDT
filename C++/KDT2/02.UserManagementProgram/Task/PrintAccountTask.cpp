#include "PrintAccountTask.h"
#include "Classes/DataBase.h"
FPrintAccountTask::FPrintAccountTask()
{
	const auto& AccountMap = GDataBase.GetAccountMap();
	cout << "[---------------------------]" << endl;
	cout << "[------    Account    ------]" << endl;
	for (auto& it : AccountMap)
	{
		cout << format("->ID : {}, PW : {} \n", it.first,it.second.Password);
	}
	cout << "[---------------------------]" << endl;
}
