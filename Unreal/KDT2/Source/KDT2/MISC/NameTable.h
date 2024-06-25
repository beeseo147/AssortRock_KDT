// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct KDT2_API FCollisionPresetNameTable
{
	static inline FName Player = TEXT("Player");
	static inline FName PlayerDetect = TEXT("PlayerDetect");
	static inline FName PlayerProjectile = TEXT("PlayerProjectile");
	static inline FName Enemy = TEXT("Enemy");
};

struct KDT2_API FCollisionChannel
{
	static inline ECollisionChannel EnemyChannel = ECollisionChannel::ECC_GameTraceChannel3;
};