#pragma once
#include "MISC/Headers.h"
#include "Player.h"
#include "Account.h"
class FLoginSession
{
public:
	std::pair<FPlayer*,const char*> Login(const FAccount& InAccount);
	bool IsLogin(const FAccountName& InAccountName);
	std::pair<bool, const char*> Logout(const FAccount& InAccount);
	const unordered_map<FAccountName, FPlayer> GetPlayerMap() const { return PlayerMap; }
private:
	unordered_map<FAccountName, FPlayer> PlayerMap;
};

inline FLoginSession GLoginSession;