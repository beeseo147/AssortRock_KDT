// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameMode/TankGameModeBase.h"
#include "Actors/Controller/TankPlayerController.h"
#include "Actors/Tank/NewTank.h"

ATankGameModeBase::ATankGameModeBase()
{
	PlayerControllerClass = ATankPlayerController::StaticClass();
	{
		ConstructorHelpers::FClassFinder<ANewTank> Class = TEXT("/Script/Engine.Blueprint'/Game/KDT2/Blueprint/Tank/NewTank.NewTank_C'");
		ensure(Class.Class);
		DefaultPawnClass = Class.Class;
	}
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ProjectilePool.Create(GetWorld(), AProjectile::StaticClass(), 50);
}

void ATankGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ProjectilePool.Destroy();
}
