#include "ProjectGameInstance.h"
#include "ProjectGameMode.h"

void UProjectGameInstance::Initialize()
{
	Super::Initialize();
}

void UProjectGameInstance::StartGameInstance()
{
	Super::StartGameInstance();

	UClass::LogReflectionData(this);
}

UProjectGameInstance::UProjectGameInstance()
{

}

UProjectGameInstance::~UProjectGameInstance()
{
	
}