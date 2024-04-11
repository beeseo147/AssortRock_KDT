// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FActorPool
{
	FActorPool();
	~FActorPool();

	void Create(UWorld* World, TSubclassOf<AActor> Class, uint32 Count);
	void Destroy();

	template<class T>
	T* New(bool bEnableCollision = true, AActor* Owner = nullptr, AActor* Instigator = nullptr)
	{
		AActor* Actor = nullptr;
		if (Pool.Num() == 0)
		{
			Actor = ActiveActors(0);
			ActiveActors;
		}
		else
		{

		}

	}

	TArray<AActor> Pool;

	//Pool에서 꺼내서 외부에서 처리되고 있는 Actor
	TArray<AActor*> ActiveActors;
};
