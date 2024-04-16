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
	T* New(const FTransform& InTransform, TFunction<void(T* NewActor)>&& InitCallback = nullptr, bool bEnableCollision = true, AActor* Owner = nullptr, APawn* Instigator = nullptr)
	{
		AActor* Actor = nullptr;
		if (Pool.Num() == 0)
		{
			Actor = ActiveActors[0];
			Delete(Actor);
			Actor = nullptr;
		}
		// 만약 전부 활성화되어 있는 상태라면 
		// 가장 먼저 활성화 시킨 액터에서 삭제한다.
		Actor = Pool.Pop(false);

		Actor->SetOwner(Owner);
		Actor->SetInstigator(Instigator);

		T* ActorT = Cast<T>(Actor);
		check(ActorT);

		Actor->SetActorEnableCollision(bEnableCollision);
		Actor->SetActorHiddenInGame(false);
		Actor->SetActorTickEnabled(true);
		const TSet<UActorComponent*>& Components = Actor->GetComponents();
		for (UActorComponent* It : Components)
		{
			if (It->HasBeenInitialized())
			{
				It->UninitializeComponent();
			}
		}

		Actor->SetActorTransform(InTransform, false, nullptr, ETeleportType::TeleportPhysics);

		if (InitCallback)
		{
			InitCallback(ActorT);
		}

		for (UActorComponent* It : Components)
		{
			It->SetComponentTickEnabled(true);
			if (!It->HasBeenInitialized())
			{
				It->InitializeComponent();
			}
		}

		ActiveActors.Push(Actor);

		return ActorT;
	}

	void Delete(AActor* InActor)
	{
		const int32 Index = ActiveActors.Find(InActor);
		if (INDEX_NONE == Index)
		{
			check(false);
		}
		ActiveActors.RemoveAt(Index);
		Pool.Add(InActor);

		if (UFunction* Function = InActor->FindFunction(TEXT("OnActorPoolBeginDelete")))
		{
			InActor->ProcessEvent(Function, nullptr);
		}

		if (AActor* ParentActor = InActor->GetAttachParentActor())
		{
			InActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}

		InActor->SetActorEnableCollision(false);
		InActor->SetActorHiddenInGame(true);
		InActor->SetActorTickEnabled(false);
		const TSet<UActorComponent*>& Components = InActor->GetComponents();
		for (UActorComponent* It : Components)
		{
			It->SetComponentTickEnabled(false);
			if (It->HasBeenInitialized())
			{
				It->UninitializeComponent();
			}
		}
	}

	TArray<AActor*> Pool;

	// Pool에서 꺼내서 외부에서 처리되고 있는 Actor
	TArray<AActor*> ActiveActors;
};