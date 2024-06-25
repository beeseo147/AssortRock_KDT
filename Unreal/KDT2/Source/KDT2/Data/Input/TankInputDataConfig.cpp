// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Input/TankInputDataConfig.h"

UTankInputDataConfig::UTankInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KDT2/Blueprint/Tank/Input/IMC_Tank.IMC_Tank'") };
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KDT2/Blueprint/Tank/Input/IA_Zoom.IA_Zoom'") };
		check(Asset.Succeeded());
		Zoom = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KDT2/Blueprint/Tank/Input/IA_Fire.IA_Fire'") };
		check(Asset.Succeeded());
		Fire = Asset.Object;
	}
}
