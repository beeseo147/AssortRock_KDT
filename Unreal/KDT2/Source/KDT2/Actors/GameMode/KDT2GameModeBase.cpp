// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameMode/KDT2GameModeBase.h"
#include "Actors/Projectile/Projectile.h"

AKDT2GameModeBase::AKDT2GameModeBase()
{
	UWorld* World = GetWorld();
	UWorld* GGWorld = GWorld;
}

void AKDT2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	UWorld* GGWorld = GWorld;
}

void AKDT2GameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
