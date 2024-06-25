// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/Character/KDT2Character.h"
#include "Actors/Weapon/Weapon.h"
#include "DataSubsystem.generated.h"

struct FItemData;
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
	const FCharacterDataTableRow* FindChacter(const FName& InKey);
	const FItemData* FindItem(const FName& InKey);
	const FWeaponDataTableRow* FindWeapon(const FName& InKey);

protected:
	UPROPERTY()
	UDataTable* ProjectileDataTable;
	UPROPERTY()
	UDataTable* CharacterDataTable;
	UPROPERTY()
	UDataTable* ItemDataTable;
	UPROPERTY()
	UDataTable* WeaponDataTable;
};
