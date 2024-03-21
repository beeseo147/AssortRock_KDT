#include "LoginSession.h"
#include "DataBase.h"
std::pair<FPlayer*, const char*> FLoginSession::Login(const FAccount& InAccount)
{
	FAccount* Account =GDataBase.CheckAccount(InAccount);
	if (!Account) {
		_ASSERT(false);
		return make_pair(nullptr,"[로그인 정보를 확인할 수 없습니다]");
	}
	const bool bLogin = IsLogin(InAccount.ID);
	if (bLogin)
	{
		std::pair<bool, const char*> bLogout = Logout(InAccount);
		if (!bLogout.first) {
			_ASSERT(false);
			return make_pair(nullptr, "LogOut Failed");;
		}
	}
	pair Pair = PlayerMap.emplace(InAccount.ID,InAccount.ID);
	FPlayer& Player = Pair.first->second;

	return make_pair(&Player, "CheckOut Failed");;
}

bool FLoginSession::IsLogin(const FAccountName& InAccountName)
{
	auto it = PlayerMap.find(InAccountName);
	if (it == PlayerMap.end()) {
		return false;
	}
	return false;
}

std::pair<bool, const char*>  FLoginSession::Logout(const FAccount& InAccount)
{
	FAccount* Account = GDataBase.CheckAccount(InAccount);
	if (!Account) {
		_ASSERT(false);
		return make_pair(false, "[로그아웃 정보를 확인할 수 없습니다]");
	}
	const bool bLogin = IsLogin(InAccount.ID);
	if (bLogin)
	{
		std::pair<bool, const char*> bLogout = Logout(InAccount);
		if (!bLogout.first) {
			_ASSERT(false);
			return make_pair(false, "LogOut Failed");;
		}
	}
	PlayerMap.erase(InAccount.ID);
	return make_pair(true,"Logout");
}
