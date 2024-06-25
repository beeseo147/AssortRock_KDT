// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Input/WeaponInputDataConfig.h"

UWeaponInputDataConfig::UWeaponInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KDT2/Blueprint/Weapon/IMC_Weapon.IMC_Weapon'")};
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KDT2/Blueprint/Weapon/IA_Attack.IA_Attack'") };
		check(Asset.Succeeded());
		Attack = Asset.Object;
	}
}
