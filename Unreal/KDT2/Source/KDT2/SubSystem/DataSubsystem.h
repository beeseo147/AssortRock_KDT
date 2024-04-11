// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Actors/Tank/Projectile.h"
#include "DataSubsystem.generated.h"

/**
 *
 */
UCLASS()
class KDT2_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UDataSubsystem();

	const FProjectileDataTableRow* FindProjectile(const FName& InKey);

protected:
	UPROPERTY()
	UDataTable* ProjectileDataTable;
};
