#pragma once
#include "BasedVirtual.h"

class FDerivedVirtual : public FBaseVirtual
{
public:
	FDerivedVirtual();
	/*virtual*/ ~FDerivedVirtual();

	// override : 재정의 했다고 티를 낸다.
	void PublicMethod() override;

public:
	int DerivedPublicValue = 11;
	int DerivedPublicValue2 = 12;
};

