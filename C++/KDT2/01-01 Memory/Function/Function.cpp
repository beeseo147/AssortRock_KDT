#include "Function.h"

void AllocateWrong(int* InTarget1, int* InTarget2)
{
	InTarget1 = new int;
	InTarget2 = new int;
}

void AllocateCorrect(int** InTarget1, int** InTarget2)
{
	*InTarget1 = new int;
	*InTarget2 = new int;
}

void Delete(int* InTarget)
{
	delete InTarget;
}
