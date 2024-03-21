#pragma once
#include "MISC/Headers.h"
class FPlayer
{
public:
	FPlayer(string_view InName)
		:Name(InName)
	{
		
	}
	
	string_view GetName()const
	{
		return Name;
	}
private:
	string Name;

};

