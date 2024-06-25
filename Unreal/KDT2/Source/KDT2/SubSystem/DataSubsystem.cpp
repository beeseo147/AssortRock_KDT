// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DataSubsystem.h"
#include "Data/Item/ItemData.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{TEXT("/Script/Engine.DataTable'/Game/KDT2/Blueprint/Tank/DT_Projectile.DT_Projectile'")};
		ensure(Asset.Object);
		ProjectileDataTable = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{TEXT("/Script/Engine.DataTable'/Game/KDT2/Blueprint/RPG/DT_Character.DT_Character'")};
		ensure(Asset.Object);
		CharacterDataTable = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{TEXT("/Script/Engine.DataTable'/Game/KDT2/Blueprint/RPG/Inventory/DT_Item.DT_Item'")};
		ensure(Asset.Object);
		ItemDataTable = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{TEXT("/Script/Engine.DataTable'/Game/KDT2/Blueprint/Weapon/DT_Weapon.DT_Weapon'")};
		ensure(Asset.Object);
		WeaponDataTable = Asset.Object;
	}
}

const FProjectileDataTableRow* UDataSubsystem::FindProjectile(const FName& InKey)
{
	FProjectileDataTableRow* Row = ProjectileDataTable->FindRow<FProjectileDataTableRow>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

const FCharacterDataTableRow* UDataSubsystem::FindChacter(const FName& InKey)
{
	FCharacterDataTableRow* Row = CharacterDataTable->FindRow<FCharacterDataTableRow>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

const FItemData* UDataSubsystem::FindItem(const FName& InKey)
{
	FItemData* Row = ItemDataTable->FindRow<FItemData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

const FWeaponDataTableRow* UDataSubsystem::FindWeapon(const FName& InKey)
{
	FWeaponDataTableRow* Row = WeaponDataTable->FindRow<FWeaponDataTableRow>(InKey, TEXT(""));
	check(Row);
	return Row;
}
