// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Input/BasicInputDataConfig.h"

UBasicInputDataConfig::UBasicInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KDT2/Blueprint/Lobby/Input/IMC_Lobby.IMC_Lobby'")};
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KDT2/Blueprint/Lobby/Input/IA_Move.IA_Move'") };
		check(Asset.Succeeded());
		Move = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KDT2/Blueprint/Lobby/Input/IA_LookMouse.IA_LookMouse'") };
		check(Asset.Succeeded());
		Look = Asset.Object;
	}
}
