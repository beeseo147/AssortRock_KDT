#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine.generated.h"

UCLASS()
class ENGINE_API UEngine : public UObject
{
	GENERATED_BODY()
	friend class UGameInstance;
public:
	/*DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEngine);
	static UClass* StaticClass() {
		return UEngineRegisterEngineClass;
	}

	static inline UClass* UEngineRegisterEngineClass = GetPrivateStaticClassBody<UEngine>(TEXT("UEngine")
		, InternalConstructor<UEngine>, &UObject::StaticClass, nullptr);*/

	UEngine(const FObjectInitializer& X);

public:
	virtual void Init();
	virtual void Start();
	virtual void Tick(float DeltaSeconds);
	void PreExit();

protected:
	//GameInstance
	shared_ptr<UGameInstance> GameInstance;
	//World
	shared_ptr <UWorld> World;
};