// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Input/RPGInputDataConfig.h"

URPGInputDataConfig::URPGInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KDT2/Blueprint/RPG/Input/IMC_RPG.IMC_RPG'")};
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KDT2/Blueprint/RPG/Input/IA_ZoomWheel.IA_ZoomWheel'") };
		check(Asset.Succeeded());
		ZoomWheel = Asset.Object;
	}
}
