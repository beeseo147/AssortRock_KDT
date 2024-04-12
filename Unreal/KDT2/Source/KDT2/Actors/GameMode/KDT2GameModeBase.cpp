// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameMode/KDT2GameModeBase.h"
#include "Actors/Tank/Projectile.h"

void AKDT2GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ProjectilePool.Create(GetWorld(), AProjectile::StaticClass(), 50);
}

void AKDT2GameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ProjectilePool.Destroy();
}
