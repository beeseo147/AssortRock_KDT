#include "BasedVirtual.h"

FBaseVirtual::FBaseVirtual()
{
	std::cout << __FUNCTION__ << std::endl;
}

FBaseVirtual::~FBaseVirtual()
{
	std::cout << __FUNCTION__ << std::endl;
}

void FBaseVirtual::PublicMethod()
{
	std::cout << __FUNCTION__ << std::endl;
}
