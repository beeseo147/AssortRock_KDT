#include "Item.h"
#include "Actors/Controller/RPGPlayerController.h"
#include "Actors/Character/KDT2Character.h"
#include "Engine/DamageEvents.h"
#include "Data/Item/ItemData.h"
#include "Subsystem/DataSubsystem.h"

void UItem_Potion::UseItem(ARPGPlayerController* Controller, FItemData& ItemData)
{
	FDamageEvent DamageEvent;
	Controller->GetPawn()->TakeDamage(10.f, DamageEvent, nullptr, nullptr);
}

void UItem_Weapon::UseItem(ARPGPlayerController* Controller, FItemData& ItemData)
{
	APawn* Pawn = Controller->GetPawn();
	AKDT2Character* Character = Cast<AKDT2Character>(Pawn);
	ensure(Character);

	UDataSubsystem* DataSubsystem = Controller->GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	const FWeaponDataTableRow* WeaponDataTableRow = DataSubsystem->FindWeapon(ItemData.ItemName);
	Character->SetWeaponData(WeaponDataTableRow);
}

void UItem_Weapon::UnEquipItem(ARPGPlayerController* Controller, FItemData& ItemData)
{
	APawn* Pawn = Controller->GetPawn();
	AKDT2Character* Character = Cast<AKDT2Character>(Pawn);
	ensure(Character);

	UDataSubsystem* DataSubsystem = Controller->GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	const FWeaponDataTableRow* WeaponDataTableRow = DataSubsystem->FindWeapon(TEXT("Fist"));
	Character->SetWeaponData(WeaponDataTableRow);
}
