// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DataSubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/KDT2/Blueprint/Tank/DT_Projectile.DT_Projectile'") };
		ensure(Asset.Object);
		ProjectileDataTable = Asset.Object;
	}
}//데이터 테이블 찾기

const FProjectileDataTableRow* UDataSubsystem::FindProjectile(const FName& InKey)
{
	FProjectileDataTableRow* Row = ProjectileDataTable->FindRow<FProjectileDataTableRow>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}
