// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MISC/MISC.h"
#include "KDT2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API AKDT2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	FActorPool& GetProjectilePool() { return ProjectilePool; }
protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
protected:

	FActorPool ProjectilePool;
};
